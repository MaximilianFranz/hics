/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>
#include <fstream>
#include <cstring>

#include <ResultException.h>
#include <ResourceException.h>
#include <Helper.h>

#include "FpgaConvolutionFunction.h"


// Threadblock sizes (e.g. for kernels GEMM1 or GEMM2)
#define TS 32

// RTS = TS / WPT
#define WPT 8

#define WIDTH 4

FpgaConvolutionFunction::FpgaConvolutionFunction(cl_context c, cl_device_id d)
        : context(c), device(d) {

    cl_int status = 0;
    queue = clCreateCommandQueue(context, device, 0, &status);
    helper::CheckError<ResourceException>(status, "Failed to create command queue.");

    std::string binary_file = helper::getBoardBinaryFile(RES_DIR "kernels/gemm4_fpga", device);
    program = helper::createProgramFromBinary(context, binary_file.c_str(), &device, 1);

    // We can't pass runtime parameters to the kernel, so just pass ""
    status = clBuildProgram(program, 0, NULL, "", NULL, NULL);
    helper::CheckError<ResourceException>(status, "Failed to build program.");

    // Check for compilation errors
    size_t logSize;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    char* messages = (char*)malloc((1+logSize)*sizeof(char));
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, messages, NULL);
    messages[logSize] = '\0';
    if (logSize > 10) { printf(">>> Compiler message: %s\n", messages); }
    free(messages);

    kernel = clCreateKernel(program, "GEMM4", NULL);

}



void FpgaConvolutionFunction::execute(const DataWrapper &input,
                                      DataWrapper &output,
                                      const WeightWrapper &weights,
                                      int stride,
                                      int filterSize,
                                      int numFilters,
                                      int zeroPadding) {

    int numPlanes = input.getDimensions()[0];
    int numRows = input.getDimensions()[1];

    /* im2col */
    int input_size = numRows;
    int channels = numPlanes;
    int kernel_size = filterSize;
    int number_of_kernels = numFilters;
    int padding = zeroPadding;

    int output_size = (input_size - kernel_size + 2 * padding) / stride + 1;

    int weights_columns, patch_rows;
    weights_columns = patch_rows = kernel_size * kernel_size * channels;
    int patch_columns = output_size * output_size;


    std::vector<float> patch_result(static_cast<unsigned long>(patch_rows * patch_columns));

    auto in = input.getData();
    auto we = weights.getData();
    helper::im2col_cpu(in.data(),
                       channels, input_size, input_size,
                       kernel_size,
                       padding,
                       stride,
                       patch_result.data());

    // Pad matrices and convert to column major format
    unsigned int K = weights_columns;
    unsigned int M = number_of_kernels;
    unsigned int N = patch_columns;

    int paddedK = 0;
    int paddedM = 0;
    int paddedN = 0;

    float *tempA = helper::add_padding(TS, K, M, we.data(), &paddedK, &paddedM);
    float *A = helper::transpose(paddedK, paddedM, tempA);
    delete tempA;

    float *tempB = helper::add_padding(TS, N, K, patch_result.data(), &paddedN, &paddedK);
    float *B = helper::transpose(paddedN, paddedK, tempB);
    delete tempB;

    float *C = new float[paddedM*paddedN];

    // Bias
    float *D = new float[paddedM];
    memset(D, 0, paddedM*sizeof(float));
    memcpy(D, weights.getBiasArray(), number_of_kernels*sizeof(float));


    // Remember unpadded values, we'll need them again later for the unpadding
    int unpaddedN = N;
    int unpaddedM = M;

    K = paddedK; //weights_columns;
    M = paddedM; //number_of_kernels;
    N = paddedN; //patch_columns;

    // Prepare OpenCL memory objects
    cl_mem bufA = clCreateBuffer(context, CL_MEM_READ_ONLY,  M*K*sizeof(float), NULL, NULL);
    cl_mem bufB = clCreateBuffer(context, CL_MEM_READ_ONLY,  K*N*sizeof(float), NULL, NULL);
    cl_mem bufC = clCreateBuffer(context, CL_MEM_READ_WRITE, M*N*sizeof(float), NULL, NULL);
    cl_mem bufD = clCreateBuffer(context, CL_MEM_READ_ONLY,  M*sizeof(float), NULL, NULL);

    // Copy matrices to the FPGA
    clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, M*K*sizeof(float), A, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, K*N*sizeof(float), B, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0, M*N*sizeof(float), C, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufD, CL_TRUE, 0, M*sizeof(float), D, 0, NULL, NULL);


    // Configure the GEMM kernel and set its arguments
    clSetKernelArg(kernel, 0, sizeof(int), (void*)&M);
    clSetKernelArg(kernel, 1, sizeof(int), (void*)&N);
    clSetKernelArg(kernel, 2, sizeof(int), (void*)&K);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&bufA);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&bufB);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&bufC);
    clSetKernelArg(kernel, 6, sizeof(cl_mem), (void*)&bufD);

    const size_t local[3] = { TS/WIDTH, TS, 1 };
    const size_t global[2] = { M/WIDTH, N };
    cl_event event;
    cl_int result = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global, local, 0, NULL, &event);
    helper::CheckError<ResultException>(result, "Failed to enqueue kernel.");

    // Wait for calculations to be finished
    clWaitForEvents(1, &event);

    // Copy the output matrix C back to the CPU memory
    clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, M*N*sizeof(float), C, 0, NULL, NULL);

    // Remove padding and transform it back to row major format
    float *transC = helper::transpose(M, N, C);
    float *unpaddedC = helper::remove_padding(TS, unpaddedN, unpaddedM, transC);

    memcpy(output.getDataArray(), unpaddedC, unpaddedN*unpaddedM*sizeof(float));

    delete [] transC;
    delete [] unpaddedC;

    // Free the OpenCL memory objects
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);
    clReleaseMemObject(bufD);

    // Free the OpenCL event objects
    clReleaseEvent(event);

    // Free the host memory objects
    delete [] A;
    delete [] B;
    delete [] C;
    delete [] D;
}

FpgaConvolutionFunction::~FpgaConvolutionFunction() {
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
}
