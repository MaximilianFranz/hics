//
// Created by Maximilian Franz on 09.01.18.
//

#include <iostream>

#include "WrapperTest.h"
#include "wrapper/DataWrapper.h"

TEST_CASE("Return functions of Wrapper", "[wrapper]") {
    std::vector<float> data(5,1.0);
    std::vector<int> s(1,5);
    DataWrapper d(s, data);
    std::string examplepath = "src/test/somefile.jpg";

    REQUIRE(d.getNumDimensions() == 1);
    REQUIRE(d.getDimensions()[0] == 5);
    REQUIRE(d.getSizeOfDimension(1) == 5);
}

SCENARIO("Writing data in empty wrapper", "[wrapper]") {
    std::vector<int> dimensions = {5};
    DataWrapper d(dimensions);
    REQUIRE(d.getNumDimensions() == 1);
    REQUIRE(d.getNumElements() == 5);

    SECTION("Elements changed in data array are changed in vector too") {
        //This is how one could pass an output to the OpenCL kernels for example.
        float *write = d.getDataArray();
        write[0] = 1;
        write[1] = 2;
        REQUIRE(d.getData()[0] == 1);
    }

    SECTION("can't write whole array on vector") {
        float a[] = {1, 2, 3, 4, 5};
        float *write = d.getDataArray();
        *write = *a;
        REQUIRE(d.getData()[2] != 3);
    }
}


SCENARIO("multidimensional positioning test") {
    std::vector<int> dim = {5, 10, 10};
    std::vector<float> data(500);
    for(int i = 0; i < 500; i++) {
        data[i] = i;
    }
    DataWrapper md(dim, data);
    SECTION("Number of elements calculated correctly") {
        REQUIRE(md.getNumElements() == 500);
        REQUIRE(md.getNumDimensions() == 3);
    }
    SECTION("Element located correctly in 3-dimensions"){
        std::vector<int> testlocation = {3, 2, 5};
        REQUIRE(md.getElement(testlocation) == 325);
    }
}
