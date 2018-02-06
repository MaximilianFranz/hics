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
    std::vector<ComputationHost*> computationHosts;

    MainWindowHandler *mainWindowHandler = nullptr;

public:

    Manager();

    /**
     * called by GUI to update the Manager when the classify is pressed
     */
    virtual void update();

    void initGUI();

    bool operator==(const ManagerObserver &managerObserver) override;

    /**
     * Intersects the available neural nets of each computation host, to only hand neural nets available on every
     * host to the Gui.
     * @return
     */
    static std::vector<NetInfo*> netIntersection(std::vector<std::vector<NetInfo*>> &allNets);
};
