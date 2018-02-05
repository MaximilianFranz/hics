//
// Created by jallmenroeder on 07/01/18.
//

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

    ComputationHost *executor = nullptr;

    MainWindowHandler *mainWindowHandler = nullptr;

public:

    Manager();

    /**
     * called by GUI to update the Manager when the classify is pressed
     */
    virtual void update();

    void initGUI();

    bool operator==(const ManagerObserver &managerObserver) override;
};
