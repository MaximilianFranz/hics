//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include "ManagerObserver.h"


/**
 * The manager is the entry point to the system. It observes the GUI and creates all other modules needed for a
 * Classification.
 */
class Manager : public ManagerObserver {
    /**
     * called by GUI to update the Manager when the classify is pressed
     */
    void update();
};
