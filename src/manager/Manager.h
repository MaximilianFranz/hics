//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include "ManagerObserver.h"

class Manager : public ManagerObserver {
    /**
     * called by GUI to update the Manager when the classify is pressed
     */
    void update();
};
