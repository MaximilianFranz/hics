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

#include <NetInfo.h>
#include <Manager.h>
#include <iostream>
#include "catch.hpp"

SCENARIO("Manager Class Tests") {

    SECTION("Test netIntersection") {
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


        std::vector<NetInfo *> nets1 = {net1, net2, net3, net10};
        std::vector<NetInfo *> nets2 = {net4, net5, net6};
        std::vector<NetInfo *> nets3 = {net7, net8, net9};

        std::vector<std::vector<NetInfo *>> allNets = {nets1, nets2, nets3};

        std::vector<NetInfo *> intersection = Manager::netIntersection(allNets);

        REQUIRE(intersection.size() == 2);
        REQUIRE(intersection[0]->getIdentifier() == "alexNet");
        REQUIRE(intersection[1]->getIdentifier() == "googLeNet");
    }

    SECTION("ManagerObserver") {
        ManagerObserver* m1 = new Manager();
        ManagerObserver* m2 = new Manager();
        REQUIRE_FALSE(m1 == m2);
    }
}