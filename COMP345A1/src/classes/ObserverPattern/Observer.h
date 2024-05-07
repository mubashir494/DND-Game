//! @file
//! @brief File containing the definition of the Observer class
//!


#pragma once
#include "Subject.h"

//Needs to have a forward reference due to
//circular reference between Observer and Subject
class Subject;

class Observer{
public:

    //! virtual destructor of the Observer class
    virtual ~Observer();

    //! pure virtual method, that children must implement to update the state
    virtual void update() = 0;

protected:
    Observer();
};