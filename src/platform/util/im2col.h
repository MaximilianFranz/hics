#pragma once

namespace helper {

    /**
     * Performs the im2col algorithm on the CPU.
     *
     * @tparam Dtype
     * @param data_image
     * @param channels
     * @param height
     * @param width
     * @param kernel_size
     * @param padding
     * @param stride
     * @param data_column
     */
    template<typename Dtype>
    void im2col_cpu(const Dtype *data_image, const int channels, const int height, const int width,
                    const int kernel_size, const int padding, const int stride,
                    Dtype *data_column);

    template<typename Dtype>
    void im2col_simple_version_cpu(const Dtype *data_image, const int channels, const int height, const int width,
                                   const int kernel_size, const int padding, const int stride,
                                   Dtype *data_column);

    /**
     * Initializes data with a value. Necessary for the col2im algorithm.
     *
     * @tparam Dtype            a data type
     * @param object_size       the size of the data type, typically height * width * channels
     * @param fill_byte         this character (typicalls 0) gets copied into the object pointed to by destination.
     * @param object_to_fill    in the col2im algorithm, this would be the im (image).
     */
    template<typename Dtype>
    void set(const int object_size, const Dtype fill_byte, Dtype *object_to_fill);


    /**
     * Performs the col2im algorithm on the CPU.
     *
     * @tparam Dtype
     * @param data_column
     * @param channels
     * @param height
     * @param width
     * @param kernel_size
     * @param padding
     * @param stride
     * @param data_image
     */
    template<typename Dtype>
    void col2im_cpu(const Dtype *data_column, const int channels, const int height, const int width,
                    const int kernel_size, const int padding, const int stride,
                    Dtype *data_image);

    template<typename Dtype>
    void col2im_simple_version_cpu(const Dtype *data_column, const int channels, const int height, const int width,
                                   const int kernel_size, const int padding, const int stride,
                                   Dtype *data_image);
}
