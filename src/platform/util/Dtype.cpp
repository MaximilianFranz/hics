#include "Dtype.h"

Dtype::Dtype(const std::vector<float> &data) : data(data) {}

const std::vector<float> &Dtype::getData() const {
    return data;
}
