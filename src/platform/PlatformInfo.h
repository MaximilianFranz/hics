//
// Created by michael on 07.01.18.
//

#pragma once

#include "string"
#include <platforms/PlatformType.h>

class PlatformInfo {
private:
    std::string description;    /*!< discription of the platform to show in the GUI */
    PlatformType type;          /*!< type of platform */
    std::string platformId;     /*!< unique identifier */
    int powerConsumption;       /*!< power consumption in mW */
    int flops;                  /*!< flops of platform */

public:
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

    //Empty default constructor
    PlatformInfo();

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
