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


#include <PlatformInfo.h>
#include <map>
#include <vector>

/**
 * Wraps up data about the performance of a classification. This includes the power needed, the computation time and
 * the usage in percent each platform of a computation host took part in the computation.
 */
class PerformanceData {
private:
    int PowerConsumption;                                           /*!< power consumption of the computation in ws */
    int ComputationTime;                                            /*!< computation time of the classification in ms*/
    std::vector<std::pair<PlatformInfo*, float>> platformUsage;      /*!< maps each platform to its percentage of the
 *                                                                       computation*/

public:
    /**
     * Creates a new PerformanceData object
     * @param PowerConsumption
     * @param ComputationTime
     * @param platformUsage
     */
    PerformanceData(int PowerConsumption, int ComputationTime,
                    const std::vector<std::pair<PlatformInfo*, float>> &platformUsage);

    /**
     *
     * @return
     */
    int getPowerConsumption() const;

    /**
     *
     * @return
     */
    int getComputationTime() const;

    /**
     *
     * @return
     */
    const std::vector<std::pair<PlatformInfo*, float>> &getPlatformUsage() const;
};
