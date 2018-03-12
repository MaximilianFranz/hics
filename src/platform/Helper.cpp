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

/*
 * Helpful links to understand im2col:
 * https://petewarden.com/2015/04/20/why-gemm-is-at-the-heart-of-deep-learning/
 * http://cs231n.github.io/convolutional-networks/
 * https://github.com/BVLC/caffe
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <unistd.h>

#include <ResultException.h>
#include <ResourceException.h>

#include "Helper.h"

namespace helper {

    void multiply_matrices_using_1d_vectors(const float *matrix_left,
                                            const int matrix_left_rows, const int matrix_left_columns,
                                            const float *matrix_right,
                                            const int matrix_right_rows, const int matrix_right_columns,
                                            float *result_matrix) {
        const auto result_matrix_columns = matrix_right_columns;
        for (int m = 0; m < matrix_left_rows; m++) {
            for (int n = 0; n < matrix_right_columns; n++) {
                float value = 0.f;
                for (int k = 0; k < matrix_right_rows; k++) {
                    value += matrix_left[m * matrix_left_columns + k] * matrix_right[k * matrix_right_columns + n];
                }
                result_matrix[m * result_matrix_columns + n] = value;
            }
        }
    }

    float *add_padding(int padding, int sizeX, int sizeY, const float *input, int *newX, int *newY) {
        int paddedX = sizeX;
        int paddedY = sizeY;

        if (sizeX % padding != 0) {
            paddedX = ((sizeX / padding) + 1) * padding;
        }
        if (sizeY % padding != 0) {
            paddedY = ((sizeY / padding) + 1) * padding;
        }

        float *out = new float[paddedX * paddedY];
        memset(out, 0, paddedX * paddedY * sizeof(float));

        float *dest = out;
        const float *src = input;
        for (int i = 0; i < sizeY; i++) {
            memcpy(dest, src, sizeX * sizeof(float));
            dest += paddedX;
            src += sizeX;
        }

        *newX = paddedX;
        *newY = paddedY;
        return out;
    }

    float *remove_padding(int padding, int sizeX, int sizeY, const float *input) {
        int paddedX = sizeX;

        if (sizeX % padding != 0) {
            paddedX = ((sizeX / padding) + 1) * padding;
        }


        float *out = new float[sizeX * sizeY];

        float *dest = out;
        const float *src = input;
        for (int i = 0; i < sizeY; i++) {
            memcpy(dest, src, sizeX * sizeof(float));
            dest += sizeX;
            src += paddedX;
        }

        return out;
    }

    float *transpose(int sizeX, int sizeY, const float *input) {

        float *out = new float[sizeX * sizeY];

        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                out[x * sizeY + y] = input[y * sizeX + x];
            }
        }

        return out;
    }

    template<typename Dtype>
    void im2col_cpu(const Dtype *data_image, const int channels, const int height, const int width,
                    const int kernel_size, const int padding, const int stride,
                    Dtype *data_column) {

        int kernel_h, kernel_w;
        kernel_h = kernel_w = kernel_size;

        int pad_h, pad_w;
        pad_h = pad_w = padding;

        int stride_h, stride_w;
        stride_h = stride_w = stride;

        const int output_h = (height - kernel_h + 2 * pad_h) / stride_h + 1;
        const int output_w = (height - kernel_w + 2 * pad_w) / stride_w + 1;
        int channels_col = channels * kernel_size * kernel_size;

        for (int c = 0; c < channels_col; ++c) {
            int w_offset = c % kernel_w;
            int h_offset = (c / kernel_w) % kernel_h;
            int c_im = c / (kernel_h * kernel_w);

            for (int h = 0; h < output_h; ++h) {
                for (int w = 0; w < output_w; ++w) {
                    int h_pad = h * stride_h - pad_h + h_offset;
                    int w_pad = w * stride_w - pad_w + w_offset;
                    if (h_pad >= 0 && h_pad < height && w_pad >= 0 && w_pad < width) {
                        data_column[(c * output_h + h) * output_w + w] =
                                data_image[(c_im * height + h_pad) * width + w_pad];
                    } else {
                        data_column[(c * output_h + h) * output_w + w] = 0;
                    }
                }
            }
        }
    }

    // Explicit instantiation
    template void
    im2col_cpu<float>(const float *data_image, const int channels, const int height, const int width,
                      const int kernel_size, const int padding, const int stride,
                      float *data_column);

    template<typename Dtype>
    void col2im_cpu(const Dtype *data_column, const int channels, const int height, const int width,
                    const int kernel_size, const int padding, const int stride,
                    Dtype *data_image) {
        int kernel_h, kernel_w;
        kernel_h = kernel_w = kernel_size;

        int pad_h, pad_w;
        pad_h = pad_w = padding;

        int stride_h, stride_w;
        stride_h = stride_w = stride;

        int height_col = (height - kernel_h + 2 * pad_h) / stride_h + 1;
        int width_col = (width - kernel_w + 2 * pad_w) / stride_w + 1;
        int channels_col = kernel_h * kernel_w * channels;

        std::fill(data_image, data_image + width * height * channels, 0);
        for (int channel = 0; channel < channels_col; ++channel) {
            int w_offset = channel % kernel_w;
            int h_offset = (channel / kernel_w) % kernel_h;
            int c_im = channel / (kernel_h * kernel_w);

            for (int h = 0; h < height_col; ++h) {
                for (int w = 0; w < width_col; ++w) {
                    int h_pad = h * stride_h - pad_h + h_offset;
                    int w_pad = w * stride_w - pad_w + w_offset;
                    if (h_pad >= 0 && h_pad < height && w_pad >= 0 && w_pad < width) {
                        data_image[(c_im * height + h_pad) * width + w_pad] +=
                                data_column[(channel * height_col + h) * width_col + w];
                    }
                }
            }
        }
    }

    // Explicit instantiation
    template void
    col2im_cpu<float>(const float *data_column, const int channels, const int height, const int width,
                      const int kernel_size, const int padding, const int stride,
                      float *data_image);

    template<typename Dtype>
    void add_bias(Dtype *data_matrix, const Dtype *bias, int rows, int columns) {
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                data_matrix[row * columns + column] = data_matrix[row * columns + column] + bias[row];
            }
        }
    }

    // Explicit instantiation
    template void
    add_bias<float>(float *data_matrix, const float *bias, int rows, int columns);

    // LCOV_EXCL_START
    const char *getErrorString(cl_int error) {
        switch (error) {
            // run-time and JIT compiler errors
            case 0:
                return "CL_SUCCESS";
            case -1:
                return "CL_DEVICE_NOT_FOUND";
            case -2:
                return "CL_DEVICE_NOT_AVAILABLE";
            case -3:
                return "CL_COMPILER_NOT_AVAILABLE";
            case -4:
                return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
            case -5:
                return "CL_OUT_OF_RESOURCES";
            case -6:
                return "CL_OUT_OF_HOST_MEMORY";
            case -7:
                return "CL_PROFILING_INFO_NOT_AVAILABLE";
            case -8:
                return "CL_MEM_COPY_OVERLAP";
            case -9:
                return "CL_IMAGE_FORMAT_MISMATCH";
            case -10:
                return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
            case -11:
                return "CL_BUILD_PROGRAM_FAILURE";
            case -12:
                return "CL_MAP_FAILURE";
            case -13:
                return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
            case -14:
                return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
            case -15:
                return "CL_COMPILE_PROGRAM_FAILURE";
            case -16:
                return "CL_LINKER_NOT_AVAILABLE";
            case -17:
                return "CL_LINK_PROGRAM_FAILURE";
            case -18:
                return "CL_DEVICE_PARTITION_FAILED";
            case -19:
                return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

                // compile-time errors
            case -30:
                return "CL_INVALID_VALUE";
            case -31:
                return "CL_INVALID_DEVICE_TYPE";
            case -32:
                return "CL_INVALID_PLATFORM";
            case -33:
                return "CL_INVALID_DEVICE";
            case -34:
                return "CL_INVALID_CONTEXT";
            case -35:
                return "CL_INVALID_QUEUE_PROPERTIES";
            case -36:
                return "CL_INVALID_COMMAND_QUEUE";
            case -37:
                return "CL_INVALID_HOST_PTR";
            case -38:
                return "CL_INVALID_MEM_OBJECT";
            case -39:
                return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
            case -40:
                return "CL_INVALID_IMAGE_SIZE";
            case -41:
                return "CL_INVALID_SAMPLER";
            case -42:
                return "CL_INVALID_BINARY";
            case -43:
                return "CL_INVALID_BUILD_OPTIONS";
            case -44:
                return "CL_INVALID_PROGRAM";
            case -45:
                return "CL_INVALID_PROGRAM_EXECUTABLE";
            case -46:
                return "CL_INVALID_KERNEL_NAME";
            case -47:
                return "CL_INVALID_KERNEL_DEFINITION";
            case -48:
                return "CL_INVALID_KERNEL";
            case -49:
                return "CL_INVALID_ARG_INDEX";
            case -50:
                return "CL_INVALID_ARG_VALUE";
            case -51:
                return "CL_INVALID_ARG_SIZE";
            case -52:
                return "CL_INVALID_KERNEL_ARGS";
            case -53:
                return "CL_INVALID_WORK_DIMENSION";
            case -54:
                return "CL_INVALID_WORK_GROUP_SIZE";
            case -55:
                return "CL_INVALID_WORK_ITEM_SIZE";
            case -56:
                return "CL_INVALID_GLOBAL_OFFSET";
            case -57:
                return "CL_INVALID_EVENT_WAIT_LIST";
            case -58:
                return "CL_INVALID_EVENT";
            case -59:
                return "CL_INVALID_OPERATION";
            case -60:
                return "CL_INVALID_GL_OBJECT";
            case -61:
                return "CL_INVALID_BUFFER_SIZE";
            case -62:
                return "CL_INVALID_MIP_LEVEL";
            case -63:
                return "CL_INVALID_GLOBAL_WORK_SIZE";
            case -64:
                return "CL_INVALID_PROPERTY";
            case -65:
                return "CL_INVALID_IMAGE_DESCRIPTOR";
            case -66:
                return "CL_INVALID_COMPILER_OPTIONS";
            case -67:
                return "CL_INVALID_LINKER_OPTIONS";
            case -68:
                return "CL_INVALID_DEVICE_PARTITION_COUNT";

                // extension errors
            case -1000:
                return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
            case -1001:
                return "CL_PLATFORM_NOT_FOUND_KHR";
            case -1002:
                return "CL_INVALID_D3D10_DEVICE_KHR";
            case -1003:
                return "CL_INVALID_D3D10_RESOURCE_KHR";
            case -1004:
                return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
            case -1005:
                return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
            default:
                return "Unknown OpenCL error";
        }
    }
    // LCOV_EXCL_STOP

    template<typename T>
    void checkError(cl_int error, const std::string &message) {
        if (error != CL_SUCCESS) {
            throw T(message + " OpenCL message: " + getErrorString(error)); // LCOV_EXCL_LINE
        }
    }

    // Explicit instantiation
    template void
    checkError<ResultException>(cl_int error, const std::string &message);

    template void
    checkError<ResourceException>(cl_int error, const std::string &message);

    std::string loadKernel(const char *name) {
        std::ifstream in(name);
        std::string result((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        return result;
    }

    cl_program createProgramFromSource(cl_context context, const std::string &source) {
        // http://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clCreateProgramWithSource.html
        size_t lengths [1] = { source.size () };
        const char* sources [1] = { source.data () };

        cl_int error = 0;
        cl_program program = clCreateProgramWithSource (context, 1, sources, lengths, &error);
        helper::checkError<ResourceException>(error, "Failed to create program.");

        return program;
    }

    // LCOV_EXCL_START
    // ================================================================================================
    // private helper functions
    bool fileExists(const char *file_name) {
        return access(file_name, R_OK) != -1;
    }

    // Loads a file in binary form.
    unsigned char *loadBinaryFile(const char *file_name, size_t *size) {
        // Open the File
        FILE *fp;
        fp = fopen(file_name, "rb");
        if (fp == 0) {
            return NULL;
        }

        // Get the size of the file
        fseek(fp, 0, SEEK_END);
        *size = ftell(fp);

        // Allocate space for the binary
        unsigned char *binary = new unsigned char[*size];

        // Go back to the file start
        rewind(fp);

        // Read the file into the binary
        if (fread((void *) binary, *size, 1, fp) == 0) {
            delete [] binary;
            fclose(fp);
            return NULL;
        }

        return binary;
    }

    std::string getDeviceName(cl_device_id did) {
        cl_int status;

        size_t sz;
        status = clGetDeviceInfo(did, CL_DEVICE_NAME, 0, NULL, &sz);
        helper::checkError<ResourceException>(status, "Failed to get device name size.");

        char *name = new char[sz];
        status = clGetDeviceInfo(did, CL_DEVICE_NAME, sz, name, NULL);
        helper::checkError<ResourceException>(status, "Failed to get device name.");

        return std::string(name);
    }
    // =================================================================================================

    std::string getBoardBinaryFile(const char *prefix, cl_device_id device) {
        const char *const VERSION_STR = "140";

        // First check if <prefix>.aocx exists. Use it if it does.
        std::string file_name = std::string(prefix) + ".aocx";
        if (fileExists(file_name.c_str())) {
            return file_name;
        }

        // Now get the name of the board. For Altera SDK for OpenCL boards,
        // the name of the device is presented as:
        //  <board name> : ...
        std::string device_name = getDeviceName(device);

        // Now search for the " :" in the device name.
        size_t end = device_name.find(" :");
        if (end != std::string::npos) {
            std::string board_name(device_name, 0, end);

            // Look for a AOCX with the name <prefix>_<board_name>_<version>.aocx.
            file_name = std::string(prefix) + "_" + board_name + "_" + VERSION_STR + ".aocx";
            if (fileExists(file_name.c_str())) {
                return file_name;
            }
        }

        // At this point just use <prefix>.aocx. This file doesn't exist
        // and this should trigger an error later.
        return std::string(prefix) + ".aocx";
    }

    // Create a program for all devices associated with the context.
    cl_program createProgramFromBinary(cl_context context, const char *binary_file_name, const cl_device_id *devices,
                                       unsigned num_devices) {
        // Early exit for potentially the most common way to fail: AOCX does not exist.
        if (!fileExists(binary_file_name)) {
            helper::checkError<ResourceException>(CL_INVALID_PROGRAM, "Failed to load binary file, AOCX file does not exist.");
        }

        // Load the binary.
        size_t binary_size;
        unsigned char *binary = loadBinaryFile(binary_file_name, &binary_size);
        if (binary == NULL) {
            helper::checkError<ResourceException>(CL_INVALID_PROGRAM, "Failed to load binary file.");
        }

        size_t binary_lengths[num_devices];
        unsigned char *binaries[num_devices];
        for (unsigned i = 0; i < num_devices; ++i) {
            binary_lengths[i] = binary_size;
            binaries[i] = binary;
        }

        cl_int status;
        cl_int binary_status[num_devices];

        cl_program program = clCreateProgramWithBinary(context, num_devices, devices, binary_lengths,
                                                       (const unsigned char **) binaries, binary_status, &status);
        helper::checkError<ResourceException>(status, "Failed to create program with binary.");
        for (unsigned i = 0; i < num_devices; ++i) {
            helper::checkError<ResourceException>(binary_status[i], "Failed to load binary for device.");
        }

        delete [] binary;

        return program;
    }
    // LCOV_EXCL_STOP

}
