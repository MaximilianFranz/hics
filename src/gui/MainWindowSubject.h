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

#include <list>
#include <algorithm>
#include "ManagerObserver.h"

/**
 * @class   MainWindowSubject
 *
 * @brief   MainWindowSubject is an interface for ManagerObserver's to observe
 *          classes derived from MainWindowSubject.
 *
 * MainWindowSubject is the abstract subject in the observer design pattern. It offers ManagerObserver objects to attach
 * or detach themselves from the observer list to get notified when MainWindowSubject's state has changed.
 * MainWindowSubject will call update() on every ManagerObserver when the state has changed.
 *
 * @author  Patrick Deubel
 * @version 1.0
 * @date    16.01.2018
 *
 */
class MainWindowSubject {

private:

    std::vector<ManagerObserver*> observers;

public:

    /**
     * @brief A ManagerObserver can be attached to the observers list.
     *
     * @param manager is the to be attached ManagerObserver
     */
    virtual void attach(ManagerObserver* manager) {
        if(observers.empty()) {
            observers.push_back(manager);
        }
    }

    /**
     * @brief A ManagerObserver who is attached to the observer list can be detached.
     *
     * @param manager is the to be detached ManagerObserver
     */
    virtual void detach(ManagerObserver* manager){
        std::vector<ManagerObserver*>::iterator it;
        it = std::find(observers.begin(), observers.end(), manager);
        observers.erase(it);
    }

    /**
     * @brief The notify method will call notify every attached ManagerObserver which means that it will call update()
     *        on each one.
     *
     * @return returns the computed ClassificationResult
     */
    virtual ClassificationResult* notify(){
        ClassificationResult* result = nullptr;
        
        for(ManagerObserver* observer : observers) {
            result = observer->update();
        }

        return result;
    }

    /**
     * @brief The default constructor for MainWindowSubject.
     */
    MainWindowSubject() = default;

    std::vector<ManagerObserver*> getObservers(){
        return observers;
    }
};
