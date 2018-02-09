
#include <iostream>
#include <fstream>

#include "FpgaConvolutionFunction.h"


// Size of the matrices - K, M, N (squared)
#define SIZE 1024

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

    queue = clCreateCommandQueue(context, device, 0, NULL);
    program = CreateProgram(LoadKernel(RES_DIR "kernels/gemm3.cl"), context);
    char cmdline[1024];
    snprintf(cmdline, 1024, "-DTS=%d -DWPT=%d -DRTS=%d", TS, WPT, TS/WPT);
    clBuildProgram(program, 0, NULL, cmdline, NULL, NULL);

    // Check for compilation errors
    size_t logSize;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    char* messages = (char*)malloc((1+logSize)*sizeof(char));
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, messages, NULL);
    messages[logSize] = '\0';
    if (logSize > 10) { printf(">>> Compiler message: %s\n", messages); }
    free(messages);

    kernel = clCreateKernel(program, "myGEMM3", NULL);

}



void FpgaConvolutionFunction::execute(const DataWrapper &input,
                                      DataWrapper &output,
                                      const WeightWrapper &weights,
                                      int stride,
                                      int filterSize,
                                      int numFilters,
                                      int zeroPadding) {
    auto b = weights.getBiasArray();
    auto w = weights.getDataArray();
    auto i = input.getDataArray();
    auto o = output.getDataArray();


    // TODO: we assume filterSize is always odd, verify if that is true
    int halfFilterSize = (filterSize -1 ) / 2;
    int numPlanes = input.getDimensions()[0];
    int numRows = input.getDimensions()[1];
    int numCols = input.getDimensions()[2];


    for (int f = 0; f < numFilters; f++) {
        int skip = halfFilterSize - zeroPadding;
        for (int inRow = skip; inRow < numRows - skip; inRow += stride) {
            for (int inCol = skip; inCol < numCols - skip; inCol += stride) {
                float sum = 0;
                for (int plane = 0; plane < numPlanes; plane++) {
                    for (int fRow = -halfFilterSize; fRow <= halfFilterSize; fRow++) {

                        if (inRow + fRow < 0 || inRow + fRow >= numRows) {
                            // Skip regions which are outside of the image, the values are 0 and don't change sum
                            continue;
                        }

                        for (int fCol = -halfFilterSize; fCol <= halfFilterSize; fCol++) {

                            if (inCol + fCol < 0 || inCol + fCol  >= numCols) {
                                // Skip regions which are outside of the image, the values are 0 and don't change sum
                                continue;
                            }

                            int c = fCol + halfFilterSize;
                            int r = fRow + halfFilterSize;
                            int wIndex = c + r*filterSize + plane*filterSize*filterSize + f*numPlanes*filterSize*filterSize;
                            float weight = w[wIndex];

                            int iIndex = (inCol + fCol) + (inRow + fRow)*numCols +  plane*numCols*numRows;
                            float data = i[iIndex];

                            sum += weight*data;
                        }

                    }

                }
                // Add bias
                sum += b[f];
                // Store result and advance pointer
                *o = sum;
                o++;

            }
        }
    }

    cl_event event = NULL;
    cl_int result;



    // Set the sizes
    int K = SIZE;
    int M = SIZE;
    int N = SIZE;

    // Create the matrices and initialize them with random values
    float* A = (float*)malloc(M*K*sizeof(float*));
    float* B = (float*)malloc(K*N*sizeof(float*));
    float* C = (float*)malloc(M*N*sizeof(float*));
    // Weights
    float* W = (float*)malloc(M*sizeof(float*));

//    for (int i=0; i<M*K; i++) { A[i] = 3.6*i + i*i + 3.1; }
//    for (int i=0; i<K*N; i++) { B[i] = 1.2*i + 0.01*i*i + 13.9; }
    for (int i=0; i<M*K; i++) { A[i] = 1; }
    for (int i=0; i<K*N; i++) { B[i] = 2; }
    for (int i=0; i<M*N; i++) { C[i] = 0.0; }
    for (int i=0; i<M; i++) { W[i] = i*i; }


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

    const size_t local[2] = { TS, TS/WPT };
    const size_t global[2] = { M, N/WPT };
    result = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global, local, 0, NULL, &event);
    CheckError(result);

    // Wait for calculations to be finished
    clWaitForEvents(1, &event);

    // Copy the output matrix C back to the CPU memory
    clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, M*N*sizeof(float), C, 0, NULL, NULL);

    float* C2 = (float*)malloc(M*N*sizeof(float*));

    for (int m=0; m<M; m++) {
        for (int n=0; n<N; n++) {
            float acc = 0.0f;
            for (int k=0; k<K; k++) {
                acc += A[k*M + m] * B[n*K + k];
            }
            acc = acc + W[m];

            C2[n*M + m] = acc;
        }
    }
    for (int i = 0; i < M*N; i++) {
        float c1 = C[i];
        float c2 = C2[i];
        if (c1 != c2) {
            std::cerr << "Failed at i " << i << std::endl;
        }
    }
    std::cout << "Finished comparing matrices" << std::endl;

    // Free the OpenCL memory objects
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);
    clReleaseMemObject(bufW);

    // Free the host memory objects
    free(A);
    free(B);
    free(C);
    free(W);
}

FpgaConvolutionFunction::~FpgaConvolutionFunction() {
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
}

