//
// Created by jallmenroeder on 09/01/18.
//

#pragma once

/**
 * This interface is implemented by the manager to observe the GUI. It follows the observer-pattern structure.
 */
class ManagerObserver {
    /**
     * Observer method for the manager to implement
     */
    virtual void update();
};
