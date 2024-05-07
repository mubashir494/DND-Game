//
// Created by hp on 12/02/2024.
//

#include "Cell.h"
#include "../Fighter/Fighter.h"
#include <iostream>

Cell::Cell() : currentState(EMPTY),content(nullptr) {
}

Cell::Cell(Cell::State state,CellContent* content) : currentState(state),content(content) {
}

Cell::State Cell::getState() {
    return currentState;
}

void Cell::setState(State state,CellContent* pContent) {
    currentState = state;
    content =  pContent;
}

bool Cell::isChest(){
    return currentState == CHEST;
}
bool Cell::isWall() {
    return currentState == WALL;
}
bool Cell::isCharacter() {
    return currentState == CHARACTER || currentState == OPPONENT;
}

bool Cell::isStart() {
    return currentState == START;
}

bool Cell::isExit() {
    return currentState == EXIT;
}

bool Cell::isEmpty() {
    return currentState == EMPTY;
}
bool Cell::isDoor(){
    return currentState == DOOR;
}


bool Cell::canMove() {
    return isStart() || isExit() || isEmpty() || isDoor();
}

Character* Cell::getCharacter() {
    if (isCharacter())
    {

        return dynamic_cast<Character*>(content);
    }
    else
    {
        return nullptr;
    }
}


// Serialization operator for Cell
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    os << static_cast<int>(cell.currentState) <<" "; // Write current state as an integer
    if(cell.currentState == Cell::State::CHEST){
        ItemContainer *pContainer = dynamic_cast<ItemContainer*>(cell.content);
        os << *pContainer ;
    }
    else if(cell.currentState == Cell::State::OPPONENT){
        Character *pCharacter = dynamic_cast<Character*>(cell.content);
        os << *pCharacter ;
    }
    return os;
}

// Deserialization operator for Cell
std::istream& operator>>(std::istream& is, Cell& cell) {
    int state; // Read the state as an integer
    is >> state;
    cell.currentState = static_cast<Cell::State>(state); // Convert integer back to State enum
    if(cell.currentState == Cell::State::CHEST){
        ItemContainer* itemContainer = new ItemContainer();
        is >> *itemContainer;
        cell.content = itemContainer;
    }
    else if(cell.currentState == Cell::State::OPPONENT){
        Character* character = new Fighter("sample",5);
        is >> *character;
        cell.content = character;
        cout << cell.content;
    }
    return is;
}

ItemContainer *Cell::getChest() {
    if (isChest())
    {
        return dynamic_cast<ItemContainer*>(content);
    }
    else
    {
        return nullptr;
    }

}

