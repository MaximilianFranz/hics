//
// Created by michael on 15.01.18.
//

#pragma once


#include <wrapper/DataWrapper.h>

class ResponseNormalizationFunction {
public:
    virtual void execute(const DataWrapper &input,
                         DataWrapper &output,
                         float radius,
                         float alpha,
                         float beta,
                         float bias) = 0;

};


