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
    std::string description;
    PlatformType type;
    std::string platformId;
    float powerConsumption;
    int flops;

public:
    PlatformInfo();

    PlatformInfo(const std::string &description, PlatformType type, const std::string &platformId,
                 float powerConsumption, int flops);

    const std::string &getString() const;

    PlatformType getType() const;

    const std::string &getPlatformId() const;

    float getPowerConsumption() const;

    int getFlops() const;
};
