//
// Created by Maximilian Franz on 22.01.18.
//


#pragma once

#include <string>
#include <map>

class LabelLoader {
public:
    /**
     * Returns the labels listed in the file as a map of output number and label string.
     * File must be structured like:
     * label1 \n
     * label2 \n
     *
     * where labels are split by newline char. Multiple descriptions for one label are possible!
     *
     * @param path
     * @return
     */
    std::map<int, std::string> getLabelMap(std::string path);

};


