//
// Created by Maximilian Franz on 09.01.18.
//

#include "WrapperTest.h"
#include "wrapper/DataWrapper.h"

TEST_CASE("Return functions of Wrapper", "[sometag]") {
    std::vector<float> data(5,1.0);
    std::vector<int> s(1,5);
    DataWrapper d(1, s, data);
    REQUIRE(d.getNumDimensions() == 1);
    std::vector<int> sizes = d.getDimensionSizes();
    REQUIRE(sizes[0] == 5);
    REQUIRE(d.getSizeOfDimension(1) == 5);
}