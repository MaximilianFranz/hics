//
// Created by michael on 15.01.18.
//

#include <wrapper/DataWrapper.h>

#include <PlatformManager.h>
#include <iostream>
#include "PlatformTest.h"

TEST_CASE("Basic test") {
    PlatformManager& pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform* p = pm.getPlatforms().at(0);
    REQUIRE(p != nullptr);

    ActivationFunction* f = p->createActivationFunction(LayerType::ACTIVATION_RELU);
    REQUIRE(f != nullptr);

    std::vector<float> data = {0, 2.2, -3.3f, 4.4, -5.5f};
    std::vector<int> s(1, 5);
    DataWrapper in(s, data);
    DataWrapper out(s);

    f->execute(in, out);
    REQUIRE(out.getData().at(0) == 0);
    REQUIRE(out.getData().at(1) == 2.2f);
    REQUIRE(out.getData().at(2) == 0);
    REQUIRE(out.getData().at(3) == 4.4f);
    REQUIRE(out.getData().at(4) == 0);

}
