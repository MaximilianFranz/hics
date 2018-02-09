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
    //TODO add pointers
    /**
     * @brief A ManagerObserver can be attached to the observers list.
     *
     * @param manager is the to be attached ManagerObserver
     */
    virtual void attach(ManagerObserver* manager) {
        observers.push_back(manager);
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
     */
    virtual void notify(){
        std::vector<ManagerObserver*>::iterator it;

        for(it = observers.begin(); it != observers.end(); ++it){
            (*it)->update();
        }
    }

    /**
     * @brief The default constructor for MainWindowSubject.
     */
    MainWindowSubject() = default;

    std::vector<ManagerObserver*> getObservers(){
        return observers;
    }
};
