//
// Created by pselab on 21.02.18.
//

#pragma once

/**
 * ENUM to identify layers by their type.
 */
enum LayerType {
    ACTIVATION_RELU,
    NORMALIZATION_LOCALRESPONSE,
    LOSS_SOFTMAX,
    POOLING_MAX,
    CONVOLUTION,
    FULLYCONNECTED,
    INPUT,
    CONCAT
};
