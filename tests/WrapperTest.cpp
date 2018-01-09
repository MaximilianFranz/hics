//
// Created by Maximilian Franz on 09.01.18.
//

#include "WrapperTest.h"
#include "../src/netbuilder/wrapper/DataWrapper.h"

TEST_CASE("Test 1", "[sometag]") {
    DataWrapper d;
    REQUIRE(d.getNumDimensions() == 5);
    REQUIRE(11 == 11);
}