//
// Created by Maximilian Franz on 22.01.18.
//


#pragma once

#include <string>
#include <map>

/**
 * Works, but only with correct path relative to runtime environment (usually in cmake-build-debug/tests/netbuilder
 */
class LabelLoader {
public:
    /**
     * Returns the labels listed in the file as a map of output number and label string.
     * File must be structured like:
     * label1 \n
     * label2, label2-alt, label2-alt2 \n
     * label3
     * where labels are split by newline char. Multiple descriptions for one label are possible!
     *
     * @param path
     * @return
     */
    static std::map<int, std::string> getLabelMap(std::string path);

};


