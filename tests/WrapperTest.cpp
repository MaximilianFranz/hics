//
// Created by Maximilian Franz on 09.01.18.
//

#include "WrapperTest.h"
#include "wrapper/DataWrapper.h"

TEST_CASE("Return functions of Wrapper", "[sometag]") {
    std::vector<float> data(5,1.0);
    std::vector<int> s(1,5);
    DataWrapper d(s, data);
    std::string examplepath = "src/test/somefile.jpg";

    REQUIRE(d.getNumDimensions() == 1);
    REQUIRE(d.getDimensions()[0] == 5);
    REQUIRE(d.getSizeOfDimension(1) == 5);
}