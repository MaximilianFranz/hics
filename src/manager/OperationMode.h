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

#pragma once

#include <IllegalArgumentException.h>

/**
 * Enum to specify the three different OperationModes. HighPower mode tries to reach the shortest possible computation
 * time without considering the power consumption, LowPower tries to classify with the least amount of power possible
 * not considering the computation time and EnergyEfficient will consider both time and power consumption to find the
 * best coefficient of computation time and power consumption.
 */
enum OperationMode {
    HighPower, LowPower, EnergyEfficient
};

struct OperationModeString {

/**
 * @brief getName returns the string representation of a given OperationMode.
 * @param mode is the OperationMode for which the string representation is wanted
 * @return the string representation
 */
    static std::string const getName(const OperationMode mode) {
        switch (mode) {
            case HighPower:
                return "High power";

            case LowPower:
                return "Low power";

            case EnergyEfficient:
                return "Energy efficient";

            // LCOV_EXCL_START
            default:
                throw IllegalArgumentException("No such operation mode");
            // LCOV_EXCL_STOP
        }
    }

    /**
     * casts a string to OperationMode enum
     * @param name string representation of enum value
     * @return OperationMode enum type
     */
    static OperationMode getMode(const std::string &name) {

        if (name == "High power") {
            return HighPower;
        } else if (name == "Low power") {
            return LowPower;
        } else if (name == "Energy efficient") {
            return EnergyEfficient;
        } else {
            throw IllegalArgumentException("No such operation mode");
        }
    }
};