//
// Created by jallmenroeder on 07/01/18.
//

#pragma once

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

            default:
                return "Operation mode";
        }
    }

};