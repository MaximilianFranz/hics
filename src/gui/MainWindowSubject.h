#pragma once

#include <list>
#include "ManagerObserver.h"

class MainWindowSubject {

private:

    std::list<ManagerObserver> observers;

public:

    void attach(const ManagerObserver &manager) {
        observers.push_back(manager);
    }

    void detach(const ManagerObserver &manager){
        observers.remove(manager);
    }

    void notify(){
        std::list<ManagerObserver>::iterator it;

        for(it = observers.begin(); it != observers.end(); ++it){
            it->update();
        }
    }

    //TODO Needed?
    MainWindowSubject();
};
