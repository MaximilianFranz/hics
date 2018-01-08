//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once;

#include <layers/Layer.h>

//TODO: Implement Iterator by overriding ++, () and * operations (optional for now)
class NetIterator {
//Must have virtual methods
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool hasNext() = 0;
    virtual Layer getElement() = 0;
};


