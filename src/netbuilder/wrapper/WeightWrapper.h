//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Wrapper.h"

class WeightWrapper : public Wrapper {
private:
    std::vector<float> bias;
    std::vector<int> biasDimension;

public:

    /** Create WeightWrapper by passing weight and bias data vectors
     *
     * @param numDimensions
     * @param dimensions
     * @param weights
     * @param bias
     * @param biasNumDimensions
     * @param biasDimensions
     */
    WeightWrapper(std::vector<int> dimensions, std::vector<float> &weights, std::vector<float> &bias,
                  std::vector<int> biasDimensions);



    /** Cover method for readability and semantics.
     *
     * @return
     */
    std::vector<float> getWeights();
    /**
     * \brief Cover method for readability and semantics. Calls the getDataArray().
     *
     * This is passed by reference from the vector and is mutable.
     *
     * @return pointer to the raw weight array of this WeightWrapper.
     */
    float* getWeightArray();

    /**
     *\brief Get a pointer to the raw float array containing the bias of this wrapper.
     *
     * This is passed by reference from the vector and is mutable.
     *
     * @return pointer to the raw bias array of this WeightWrapper.
     */
    const float* getBiasArray() const;

    /**
     * \brief returns the vector containing the bias of this WeightWrapper.
     *
     * @return the vector with the bias of this WeightWrapper.
     */
    std::vector<float> getBias();

    const std::vector<int> &getBiasDimension() const;
};
