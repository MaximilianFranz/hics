//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "NetIterator.h"

class SimpleNetIterator : NetIterator {
    void first() override;

    void next() override;

    bool hasNext() override;

    Layer getElement() override;

};

