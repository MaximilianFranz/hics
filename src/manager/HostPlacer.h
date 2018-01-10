//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_HOSTPLACER_H
#define HICS_HOSTPLACER_H


#include <ComputationHost.h>
#include <NetInfo.h>
#include <map>
#include <vector>


class HostPlacer {
public:
    static std::map<ComputationHost, int> place(std::vector<ComputationHost> hosts, NetInfo net, int numOfImg,
    OperationMode opMode);
};


#endif //HICS_HOSTPLACER_H
