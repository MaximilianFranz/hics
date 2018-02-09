//
// Created by Maximilian Franz on 07.01.18.
//

#include "DataWrapper.h"


DataWrapper::DataWrapper(std::vector<int> dimensions, std::vector<float> &data)
    : Wrapper(dimensions, data) {

}

DataWrapper::DataWrapper(std::vector<int> dimensions)
        : Wrapper(dimensions) {

}

DataWrapper::~DataWrapper() {
//    delete[](&data);
//    delete[](&dimensions);
//    delete[](&numElements);
}

DataWrapper::DataWrapper(const DataWrapper &wrapper) : Wrapper(wrapper) {

}
