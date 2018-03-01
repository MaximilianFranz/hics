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

#pragma once

#include <string>
#include <vector>
#include <NetInfo.h>
#include "JSONModelLoader.h"

class ModelCrawler {
private:
    static NetInfo *constructNetInfo(JSONModelLoader *loader);

    /**
     * Helper that lists all files names in a directory
     *
     * @param pathToDir from which to list file names
     * @return list of file names that are not . or ..
     * @throws ResourceExecption if directory could not be located or cannot be read
     */
    static std::vector<std::string> getFilesInDir(std::string pathToDir);

public:

    /**
     * Returns NetInfos for all valid neural net descriptions
     *
     * @param path to the directory where nets should be located
     * @return list of valid nets as NetInfo
     * @throws ResourceException if no valid nets where found
     */
    static std::vector<NetInfo*> getValidNets(std::string path);
};

