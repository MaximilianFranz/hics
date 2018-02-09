//
// Created by jallmenroeder on 06/02/18.
//
#include <NetInfo.h>
#include <Manager.h>
#include <iostream>
#include "catch.hpp"

SCENARIO("Test netIntersection") {
    auto net1 = new NetInfo("alex", 3, "alexNet");
    auto net2 = new NetInfo("goo", 3, "googLeNet");
    auto net3 = new NetInfo("fanc", 3, "fancyNet");
    auto net10 = new NetInfo("asdasd", 3, "evenMoreFancy");
    auto net6 = new NetInfo("alex", 3, "alexNet");
    auto net5 = new NetInfo("goo", 3, "googLeNet");
    auto net4 = new NetInfo("oth", 3, "otherNet");
    auto net8 = new NetInfo("alex", 3, "alexNet");
    auto net7 = new NetInfo("goo", 3, "googLeNet");
    auto net9 = new NetInfo("test", 3, "testNet");


    std::vector<NetInfo*> nets1 = {net1, net2, net3, net10};
    std::vector<NetInfo*> nets2 = {net4, net5, net6};
    std::vector<NetInfo*> nets3 = {net7, net8, net9};

    std::vector<std::vector<NetInfo*>> allNets = {nets1, nets2, nets3};

    std::vector<NetInfo*> intersection = Manager::netIntersection(allNets);

    REQUIRE(intersection.size() == 2);
    REQUIRE(intersection[0]->getIdentifier() == "alexNet");
    REQUIRE(intersection[1]->getIdentifier() == "googLeNet");
}