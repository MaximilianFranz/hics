//
// Created by Patrick Deubel on 27.01.18.
//

#include <Manager.h>
#include "MainWindowSubjectTest.h"
#include "MainWindowSubject.h"

TEST_CASE( "MainWindowSubject can attach, detach and notfiy ManagerObserver's", "[mainwindowsubject]" ) {

    MainWindowSubject subject;
    Manager observer1;
    Manager observer2;

    subject.attach(&observer1);
    subject.attach(&observer2);

    REQUIRE(subject.getObservers().size() == 2);

    SECTION ("Method attach() test" , "[attach]") {
        Manager observer3;
        subject.attach(&observer3);
        REQUIRE(subject.getObservers().size() == 3);
    }

    SECTION( "Method detach() test" , "[detach]") {
        subject.detach(&observer1);
        REQUIRE(subject.getObservers().size() == 1);
    }

/*    SECTION( "Method notify() test" , "[notify]") {
        subject.notify();
        //REQUIRE observe1 and observer 2 update has been called
        //TODO add notify test when implemented
    }*/
}
