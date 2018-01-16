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
enum OperationMode {HighPower, LowPower, EnergyEfficient};
