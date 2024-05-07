//! @file
//! @brief File containing the definition of the CharacterObserver class
//!

#pragma once
#include "Observer.h"
#include "../Character/Character.h"


class CharacterObserver: public Observer{
public:

    //! default constructor of the CharacterObserer class
    CharacterObserver();

    /**
    * @brief Create an observer to a Character
    *
    * @param character The character to be observed.
    */
    CharacterObserver(Character* character);

    //! Destructor of the CharacterObserver class
    ~CharacterObserver();

    //! method that updates the state of the CharacterObserver
    void update();

    //! method that displays the state of the CharacterObserver
    void display();


private:
    Character* _subject;

};
