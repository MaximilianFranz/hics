#pragma once

#include <list>
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

    std::list<ManagerObserver> observers;

public:

    /**
     * @brief A ManagerObserver can be attached to the observers list.
     *
     * @param manager is the to be attached ManagerObserver
     */
    void attach(const ManagerObserver &manager) {
        observers.push_back(manager);
    }

    /**
     * @brief A ManagerObserver who is attachted to the observer list can be detached.
     *
     * @param manager is the to be detached ManagerObserver
     */
    void detach(const ManagerObserver &manager){
        observers.remove(manager); //TODO maybe check if manager is in the list at all
    }

    /**
     * @brief The notify method will call notify every attached ManagerObserver which means that it will call update()
     *        on each one.
     */
    void notify(){
        std::list<ManagerObserver>::iterator it;

        for(it = observers.begin(); it != observers.end(); ++it){
            it->update();
        }
    }

    /**
     * @brief The default constructor for MainWindowSubject.
     */
    MainWindowSubject() = default;
};
