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

#include <string>
#include <platforms/PlatformType.h>

/**
 * @class PlatformInfo
 *
 * @brief PlatformInfo is a data structure for the Platform class.
 *
 * PlatformInfo provides information about the underlying platform. Its attributes are pulled from the Platform class,
 * since this information needs to be transferred across hosts via RPC. This means the Communicator must be able to
 * serialize and deserialize the data.
 */
class PlatformInfo {
private:
    std::string description;    /*!< discription of the platform to show in the GUI */
    PlatformType type;          /*!< type of platform */
    std::string platformId;     /*!< unique identifier */
    int powerConsumption;       /*!< power consumption in mW */
    int flops;                  /*!< flops of platform */

public:
    PlatformInfo();
    
    /**
     * Creates a new PlatformInfo Object containing all relevant information about a platform.
     * @param description       discription of the platform to show in the GUI
     * @param type              type of platform
     * @param platformId        unique identifier
     * @param powerConsumption  power consumption in mW
     * @param flops             flops of platform
     */
    PlatformInfo(const std::string &description, PlatformType type, const std::string &platformId, int powerConsumption,
                 int flops);

    /**
     * Returns the description.
     * @return description
     */
    const std::string &getDescription() const;

    /**
     * Returns platform type.
     * @return platform type
     */
    PlatformType getType() const;

    /**
     * Returns platform ID.
     * @return platform ID
     */
    const std::string &getPlatformId() const;

    /**
     * Returns power consumption in mW.
     * @return power consumption
     */
    int getPowerConsumption() const;

    /**
     * Returns the flops.
     * @return flops
     */
    int getFlops() const;
};
