//
// Created by Maximilian Franz on 07.01.18.
//

#include "DataWrapper.h"
#include "../../NotImplementedException.h"

int DataWrapper::getNumDimensions() {
    return 5; //TODO: replace with proper method!
}


int DataWrapper::getDimensionSizes() {
    return Wrapper::getDimensionSizes();
}

DataWrapper::DataWrapper() {
    throw NotImplementedException();
}
