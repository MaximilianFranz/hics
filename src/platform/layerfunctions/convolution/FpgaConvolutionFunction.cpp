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

#include "AOCL_Utils.h"

#include "FpgaConvolutionFunction.h"
#include "util/im2col.h"


// Threadblock sizes (e.g. for kernels myGEMM1 or myGEMM2)
#define TS 32

// RTS = TS / WPT
#define WPT 8

// =================================================================================================

const char *getErrorString(cl_int error)
{
    switch(error){
        // run-time and JIT compiler errors
        case 0: return "CL_SUCCESS";
        case -1: return "CL_DEVICE_NOT_FOUND";
        case -2: return "CL_DEVICE_NOT_AVAILABLE";
        case -3: return "CL_COMPILER_NOT_AVAILABLE";
        case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case -5: return "CL_OUT_OF_RESOURCES";
        case -6: return "CL_OUT_OF_HOST_MEMORY";
        case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
        case -8: return "CL_MEM_COPY_OVERLAP";
        case -9: return "CL_IMAGE_FORMAT_MISMATCH";
        case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
        case -11: return "CL_BUILD_PROGRAM_FAILURE";
        case -12: return "CL_MAP_FAILURE";
        case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
        case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
        case -15: return "CL_COMPILE_PROGRAM_FAILURE";
        case -16: return "CL_LINKER_NOT_AVAILABLE";
        case -17: return "CL_LINK_PROGRAM_FAILURE";
        case -18: return "CL_DEVICE_PARTITION_FAILED";
        case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

            // compile-time errors
        case -30: return "CL_INVALID_VALUE";
        case -31: return "CL_INVALID_DEVICE_TYPE";
        case -32: return "CL_INVALID_PLATFORM";
        case -33: return "CL_INVALID_DEVICE";
        case -34: return "CL_INVALID_CONTEXT";
        case -35: return "CL_INVALID_QUEUE_PROPERTIES";
        case -36: return "CL_INVALID_COMMAND_QUEUE";
        case -37: return "CL_INVALID_HOST_PTR";
        case -38: return "CL_INVALID_MEM_OBJECT";
        case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
        case -40: return "CL_INVALID_IMAGE_SIZE";
        case -41: return "CL_INVALID_SAMPLER";
        case -42: return "CL_INVALID_BINARY";
        case -43: return "CL_INVALID_BUILD_OPTIONS";
        case -44: return "CL_INVALID_PROGRAM";
        case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
        case -46: return "CL_INVALID_KERNEL_NAME";
        case -47: return "CL_INVALID_KERNEL_DEFINITION";
        case -48: return "CL_INVALID_KERNEL";
        case -49: return "CL_INVALID_ARG_INDEX";
        case -50: return "CL_INVALID_ARG_VALUE";
        case -51: return "CL_INVALID_ARG_SIZE";
        case -52: return "CL_INVALID_KERNEL_ARGS";
        case -53: return "CL_INVALID_WORK_DIMENSION";
        case -54: return "CL_INVALID_WORK_GROUP_SIZE";
        case -55: return "CL_INVALID_WORK_ITEM_SIZE";
        case -56: return "CL_INVALID_GLOBAL_OFFSET";
        case -57: return "CL_INVALID_EVENT_WAIT_LIST";
        case -58: return "CL_INVALID_EVENT";
        case -59: return "CL_INVALID_OPERATION";
        case -60: return "CL_INVALID_GL_OBJECT";
        case -61: return "CL_INVALID_BUFFER_SIZE";
        case -62: return "CL_INVALID_MIP_LEVEL";
        case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
        case -64: return "CL_INVALID_PROPERTY";
        case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
        case -66: return "CL_INVALID_COMPILER_OPTIONS";
        case -67: return "CL_INVALID_LINKER_OPTIONS";
        case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

            // extension errors
        case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
        case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
        case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
        case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
        case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
        case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
        default: return "Unknown OpenCL error";
    }
}

void CheckError (cl_int error)
{
    if (error != CL_SUCCESS) {
        std::cerr << "OpenCL call failed with error " << getErrorString(error) << std::endl;
        std::exit (1);
    }
}

std::string LoadKernel (const char* name)
{
    std::ifstream in (name);
    std::string result (
            (std::istreambuf_iterator<char> (in)),
            std::istreambuf_iterator<char> ());
    return result;
}

cl_program CreateProgram (const std::string& source,
                          cl_context context)
{
    // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateProgramWithSource.html
    size_t lengths [1] = { source.size () };
    const char* sources [1] = { source.data () };

    cl_int error = 0;
    cl_program program = clCreateProgramWithSource (context, 1, sources, lengths, &error);
    CheckError (error);

    return program;
}

// =================================================================================================

FpgaConvolutionFunction::FpgaConvolutionFunction(cl_context c, cl_device_id d)
        : context(c), device(d) {

    cl_int status = 0;
    queue = clCreateCommandQueue(context, device, 0, &status);
    aocl_utils::checkError(status, "Failed to create command queue");

    // TODO: Remove this ifdef once we have GPU platform
#ifdef ALTERA
    std::string binary_file = aocl_utils::getBoardBinaryFile("gemm1", device);
    program = aocl_utils::createProgramFromBinary(context, binary_file.c_str(), &device, 1);
#else
    program = CreateProgram(LoadKernel(RES_DIR "kernels/gemm1.cl"), context);
#endif

//    char cmdline[1024];
//    snprintf(cmdline, 1024, "-DTS=%d -DWPT=%d -DRTS=%d", TS, WPT, TS/WPT);
//    clBuildProgram(program, 0, NULL, cmdline, NULL, NULL);
    status = clBuildProgram(program, 0, NULL, "", NULL, NULL);
    aocl_utils::checkError(status, "Failed to build program");

    // Check for compilation errors
    size_t logSize;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    char* messages = (char*)malloc((1+logSize)*sizeof(char));
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, messages, NULL);
    messages[logSize] = '\0';
    if (logSize > 10) { printf(">>> Compiler message: %s\n", messages); }
    free(messages);

    kernel = clCreateKernel(program, "myGEMM1", NULL);

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
    helper::im2col_simple_version_cpu(in.data(),
                                      channels, input_size, input_size,
                                      kernel_size,
                                      padding,
                                      stride,
                                      patch_result.data());


    float* A = we.data();
    float* B = patch_result.data();
    float *C = output.getDataArray();

    // Weights
    const float* W = weights.getBiasArray();



    int K = weights_columns;
    int M = number_of_kernels;
    int N = patch_columns;



    // Prepare OpenCL memory objects
    cl_mem bufA = clCreateBuffer(context, CL_MEM_READ_ONLY,  M*K*sizeof(float), NULL, NULL);
    cl_mem bufB = clCreateBuffer(context, CL_MEM_READ_ONLY,  K*N*sizeof(float), NULL, NULL);
    cl_mem bufC = clCreateBuffer(context, CL_MEM_READ_WRITE, M*N*sizeof(float), NULL, NULL);
    cl_mem bufW = clCreateBuffer(context, CL_MEM_READ_ONLY,  M*sizeof(float), NULL, NULL);

    // Copy matrices to the GPU
    clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, M*K*sizeof(float), A, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, K*N*sizeof(float), B, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0, M*N*sizeof(float), C, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufW, CL_TRUE, 0, M*sizeof(float), W, 0, NULL, NULL);


    // Configure the myGEMM kernel and set its arguments
    clSetKernelArg(kernel, 0, sizeof(int), (void*)&M);
    clSetKernelArg(kernel, 1, sizeof(int), (void*)&N);
    clSetKernelArg(kernel, 2, sizeof(int), (void*)&K);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&bufA);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&bufB);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&bufC);
    clSetKernelArg(kernel, 6, sizeof(cl_mem), (void*)&bufW);

//    const size_t local[2] = { TS, TS };
    const size_t global[2] = { M, N };
    cl_event event;
    cl_int result = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global, NULL, 0, NULL, &event);
    CheckError(result);

    // Wait for calculations to be finished
    clWaitForEvents(1, &event);

    // Copy the output matrix C back to the CPU memory
    clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, M*N*sizeof(float), C, 0, NULL, NULL);

    // Free the OpenCL memory objects
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);
    clReleaseMemObject(bufW);

    // Free the host memory objects
//    free(A);
//    free(B);
//    free(C);

 }

FpgaConvolutionFunction::~FpgaConvolutionFunction() {
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
}

