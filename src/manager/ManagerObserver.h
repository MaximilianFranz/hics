//
// Created by jallmenroeder on 09/01/18.
//

#pragma once

#include <NotImplementedException.h>

/**
 * This interface is implemented by the manager to observe the GUI. It follows the observer-pattern structure.
 */
class ManagerObserver {

public:

    /**
     * Observer method for the manager to implement
     */
    virtual void update(){
        throw NotImplementedException();
    }

    /**
     * @brief Overloads operator==() function to compare two ManagerObserver's on their identity.
     *
     * @param managerObserver the to be compared ManagerObserver
     * @return true if they are equal, false if not.
     */
    bool operator==(const ManagerObserver &managerObserver){
        return this == &managerObserver;
    }
};
