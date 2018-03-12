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

#include <vector>

#include "platforms/Platform.h"
#include "PlatformInfo.h"

class PlatformManager {
private:
    // Private constructor
    PlatformManager();
    std::vector<Platform*> platforms;
    void init();

public:

    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    PlatformManager(PlatformManager const&) = delete;
    PlatformManager& operator=(PlatformManager const &) = delete;

    /**
     * Return the Singleton instance of the PlatformManager.
     *
     * @return      The Singleton instance of the PlatformManager.
     */
    static PlatformManager& getInstance();

    /**
     * Returns all available platforms.
     *
     * @return      The available platforms.
     */
    std::vector<Platform*> getPlatforms();

    /**
     * Returns the PlatformInfos for every available platform.
     *
     * @return      A vector containing the PlatformInfo of every available platform
     */
    std::vector<PlatformInfo*> getPlatformInfos();

    /**
     * Returns the platform with the ID @uuid.
     *
     * @param uuid  The ID of the requested platform
     * @return      The platform with the ID @uuid if it can be found, elsewise a null pointer
     */
    Platform* getPlatformById(std::string uuid);

    /**
     * Deletes all platforms and frees the memory.
     */
    void reset();
};
