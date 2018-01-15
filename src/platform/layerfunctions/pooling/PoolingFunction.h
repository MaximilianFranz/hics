//
// Created by David Culley on 12.01.18.
//

#pragma once


#include <wrapper/DataWrapper.h>

class PoolingFunction {
public:
    virtual void execute(const DataWrapper &input,
                         DataWrapper &output,
                         int stride,
                         int filterSize,
                         int zeroPadding) = 0;
};


