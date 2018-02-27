/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <fstream>
#include <ResourceException.h>
#include "LabelLoader.h"

std::map<int, std::string> LabelLoader::getLabelMap(std::string path) {

    std::map<int, std::string> labelMap;
    std::ifstream file;

    char *resolved_path = realpath(path.c_str(), NULL);
    if (resolved_path == nullptr) {
        throw ResourceException("Path to labels could not be resolved. Given relative path: " + path);
    }

    try {
        std::ifstream file(resolved_path);
    }
    catch (...) {
        throw ResourceException("Could not read label file at: " + path);
    }

    std::string line;
    int index = 0;

    // Place labels into map line by line
    while (std::getline(file, line)) {
        labelMap.emplace(std::pair<int, std::string>(index, line));
        index++;
    }

    if (labelMap.empty()) {
        throw ResourceException("No labels found in file: " + path);
    }

    free(resolved_path);
    return labelMap;
}
