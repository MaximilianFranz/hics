//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_MANAGER_H
#define HICS_MANAGER_H


#include "ManagerObserver.h"

class Manager : public ManagerObserver {
    /**
     * called by GUI to update the Manager when the classify is pressed
     */
    void update();
};


#endif //HICS_MANAGER_H
