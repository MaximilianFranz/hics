//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Wrapper.h"

class WeightWrapper : public Wrapper {
private:
    std::vector<float> bias;
    int biasNumDimensions;
    std::vector<int> biasDimensionSizes;

public:

    /** Create WeightWrapper by passing weight and bias data vectors
     *
     * @param numDimensions
     * @param dimensionSizes
     * @param weights
     * @param bias
     * @param biasNumDimensions
     * @param biasDimensionSizes
     */
    WeightWrapper(int numDimensions,
                    std::vector<int> &dimensionSizes,
                    std::vector<float> &weights,
                    std::vector<float> &bias,
                    int biasNumDimensions,
                    std::vector<int> &biasDimensionSizes)
            : Wrapper(numDimensions, dimensionSizes, weights),
              bias(bias),
              biasNumDimensions(biasNumDimensions),
              biasDimensionSizes(biasDimensionSizes) {

    }



    /** Cover method for readability
     *
     * @return
     */
    std::vector<float> getWeights() {
        return data;
    }

    float* getWeightArray() {
        return &data[0];
    }

    float* getBiasArray() {

    }

    std::vector<float> getBias() {
        return bias;
    }
};
