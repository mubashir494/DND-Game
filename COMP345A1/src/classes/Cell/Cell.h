//
// Created by hp on 12/02/2024.
//

#ifndef COMP345A1_CELL_H
#define COMP345A1_CELL_H

#include "../Character/Character.h"
#include "../CellContent/CellContent.h"

class Character;
class ItemContainer;

/**
 * This file implements the Cell class which holds the State of each cell on the Map
 * Other than it provides basic Getters and setters
 *
 * * @par Libraries Used:
 * - <iostream>: Ensures that the serialization and deserialization operators have access to the necessary stream classes and functions,
 *                allowing seamless integration of stream-based operations within the Cell class.
 */
class Cell {
public:
    /**
     * These are all the States which an Cell can contain
     */
    enum State{
        EMPTY,
        EXIT,
        START,
        WALL,
        OPPONENT,
        CHARACTER,
        CHEST,
        DOOR
    };
public:
    /**
     * Constructor which will create an Empty Cell object
     */
    Cell();
    /**
     * @brief Constructor which accepts state and creates the Cell according t
     * @param state
     */
    Cell(State state,CellContent* pContent);

    /**
     * @brief Destructor
     */
    virtual ~Cell() = default;
    /**
     * is chest
     * @return
     */
    bool isChest();
    /**
     * @brief Check whether the Cell is a Wall or not
     * @return
     */
    bool isWall();
    /**
     * @brief Check whether the cell is Character or not
     * @return
     */
    bool isCharacter();
    /**
     *@brief Check whether the cell is Start or not
     * @return
     */
    bool isStart();
    /**
     * @brief Check whether the cell is Exit or not
     * @return
     */
    bool isExit();
    /**
     * @brief Check whether the cell is Empty or not
     * @return
     */
    bool isEmpty();

    /**
     * @brief Check whether we can move one position or not
     * @return
     */
     bool canMove();

     /**
      * @brief Check whether it is a Door or Not
      * @return
      */
     bool isDoor();

    /**
     * @brief Gets the State of the cell
     * @return
     */
    State getState();


    /**
     * @brief Gets Character
     * @return
     */
    Character* getCharacter();

    /**
     * @brief gets chest on the map
     * @return
     */
    ItemContainer* getChest();
    /**
     * @brief Sets the State of the Cell
     * @param state
     */
    void setState(State state,CellContent* pContent);


    /**
     * @brief Serialization operator for Cell.
     *
     * Writes the current state of the cell as an integer to the output stream.
     *
     * @param os The output stream to write to.
     * @param cell The cell object to serialize.
     * @return The output stream after serialization.
     */
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);


    /**
     * @brief Deserialization operator for Cell.
     *
     * Reads the state of the cell as an integer from the input stream and converts it
     * back to the State enum, updating the cell's state accordingly.
     *
     * @param is The input stream to read from.
     * @param cell The cell object to deserialize into.
     * @return The input stream after deserialization.
     */
    friend std::istream& operator>>(std::istream& is, Cell& cell);



private:
    /**
     * @brief Stores the State of the Cell
     */
    State currentState;

    /**
     * @brief stores the character;
     */
    CellContent* content;
};


#endif //COMP345A1_CELL_H
