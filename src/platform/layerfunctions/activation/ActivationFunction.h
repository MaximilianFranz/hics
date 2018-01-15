//
// Created by David Culley on 12.01.18.
//

#pragma once


#include <wrapper/DataWrapper.h>

class ActivationFunction  {
public:
    virtual void execute(const DataWrapper &input, DataWrapper &output) = 0;
};


