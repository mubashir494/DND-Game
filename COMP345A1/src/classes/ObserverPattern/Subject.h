//! @file
//! @brief File containing the definition of the Subject class
//!

#pragma once
#include "Observer.h"
#include <list>

using namespace std;


//Need to have a forward reference due to
// circular reference between Observer and Subject
class Observer;

class Subject {
    public:
        //! Adds an observer to the list of observers
        virtual void Attach(Observer* o);
        //! Removes an observer from the list of observers
        virtual void Detach(Observer* o);

        //! notifies all subsribed observers
        virtual void Notify();
        Subject();

        //! virtual destructor of the Subject class
        virtual ~Subject();

    private:
        //! list of subscribed observers
        list<Observer*> *_observers;
};