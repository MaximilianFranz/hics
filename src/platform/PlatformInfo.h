//
// Created by michael on 07.01.18.
//

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
    float powerConsumption;       /*!< power consumption in mW */
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
    PlatformInfo(const std::string &description, PlatformType type, const std::string &platformId, float powerConsumption,
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
    float getPowerConsumption() const;

    /**
     * Returns the flops.
     * @return flops
     */
    int getFlops() const;
};
