
#include "CharacterObserver.h"
#include "../Character/Character.h"
#include <iostream>

using namespace std;

CharacterObserver::CharacterObserver(){
};

CharacterObserver::CharacterObserver(Character *character) {
    _subject = character;
    _subject->Attach(this);
}

CharacterObserver::~CharacterObserver() {
    _subject->Detach(this);
}

void CharacterObserver::update() {
    display();
}

void CharacterObserver::display() {
   _subject->displayCharacterSheet();
}
