#pragma once


#include <vector>

class Dtype {
private:
    std::vector<float> data;
public:
    explicit Dtype(const std::vector<float> &data);

    const std::vector<float> &getData() const;
};
