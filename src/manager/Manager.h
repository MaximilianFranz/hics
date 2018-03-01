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


#include <Executor.h>
#include "ManagerObserver.h"
#include "handler/MainWindowHandler.h"


/**
 * The manager is the entry point to the system. It observes the GUI and creates all other modules needed for a
 * Classification.
 */
class Manager : public ManagerObserver {

private:
    std::vector<ComputationHost*> computationHosts;

    MainWindowHandler *mainWindowHandler = nullptr;

public:

    Manager();

    /**
     * called by GUI to update the Manager when the classify is pressed
     *
     * @return returns the computed ClassificationResult
     */
    virtual ClassificationResult* update();

    void initGUI();

    bool operator==(const ManagerObserver &managerObserver) override;

    /**
     * Intersects the available neural nets of each computation host, to only hand neural nets available on every
     * host to the Gui.
     * @return
     */
    static std::vector<NetInfo*> netIntersection(std::vector<std::vector<NetInfo*>> &allNets);
};
