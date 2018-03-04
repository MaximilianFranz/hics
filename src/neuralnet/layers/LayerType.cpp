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

#include <ostream>

#include "LayerType.h"

std::ostream &operator<<(std::ostream &os, const LayerType &layertype) {
    switch (layertype) {
        case LayerType::ACTIVATION_RELU :
            return os << "ACTIVATION_RELU";
        case LayerType::NORMALIZATION_LOCALRESPONSE :
            return os << "NORMALIZATION_LOCALRESPONSE";
        case LayerType::LOSS_SOFTMAX :
            return os << "LOSS_SOFTMAX";
        case LayerType::POOLING_MAX :
            return os << "POOLING_MAX";
        case LayerType::CONVOLUTION :
            return os << "CONVOLUTION";
        case LayerType::FULLYCONNECTED :
            return os << "FULLYCONNECTED";
        case LayerType::INPUT :
            return os << "INPUT";
        case LayerType::CONCAT :
            return os << "CONCAT";
        // omit default case to trigger compiler warning for missing cases
    }
    return os << "<UNKNOWN>";
}