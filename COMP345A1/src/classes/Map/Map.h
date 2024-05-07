//
// Created by hp on 12/02/2024.
//
#include "../Cell/Cell.h"
#include "../ObserverPattern/Subject.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <list>
#include "../GameLogger/GameLogger.h"


#ifndef COMP345A1_MAP_H
#define COMP345A1_MAP_H



using namespace std;

class Character;
class Cell;
class ItemContainer;
struct Coordinate {
    int x;
    int y;
    Coordinate() : x(0), y(0) {}
    Coordinate(int x, int y) : x(x), y(y) {}

    bool equalCoordinates(const Coordinate& c1) {
        if(x == c1.x && y == c1.y ){
            return true;
        }
        return false;
    }
};

/**
 * @class Map
 * @brief Container class for the Cells
 *
 * Game Rules: Creates a Map with walls around, dungeon master can place Starting point,Ending point,Opponent,etc
 * and design the map
 *
 * Libraries:
 * <iostream>: Included for standard input/output operations such as printing messages to the terminal and reading user input.
 * <queue>: Used for implementing queues, which are utilized in BFS (Breadth First Search) algorithm for pathfinding in the map.
 * <map>: Utilized for storing the previous states of characters, facilitating the ability to revert their positions when necessary.
 *
 */
class Map : public Subject, IObservable{
public:
    /**
     * @brief Accepts width and height of the map and initializes a two dimensional array with Wall arround
     * @param width
     * @param height
     */
    Map(int width, int height);

    /**
     * @brief Responsible for destructing the Map object
     */
    ~Map();

    /**
     * @brief Places the item on the inputted coordinates
     * @param x
     * @param y
     * @param item (Accepts : '#' : Wall, 'S' : Starting Point, 'E' : "Ending Point", 'D' : Door, 'C' : Chest)
     * @return
     */
    bool Place(int x, int y,char item);

    /**
     * Determines whether there is path from starting point to the Ending point using Breadth first Search
     * @return
     */
    bool isValid ();


    /**
     * Prints the Map on the Terminal
     */
    void printMap();

    /**
     * Start the Game by placing a character on the map
     */
    bool placeCharacter(Character* c);

    bool placeNPC(Character* c, int x, int y);

     /**
      * Takes character pointer, direction and tries it to move on the map
      * @param c
      * @param dir
      */
     bool tryMove (Character *c,string dir);

    /**
    * @brief Serialize the Map object.
    *
    * This method serializes the Map object to an output stream. It writes the map dimensions followed by the state of each cell in the map.
    *
    * @param os The output stream to serialize the Map object to.
    * @param map The Map object to be serialized.
    * @return A reference to the output stream after serialization.
    */
    friend std::ostream& operator<<(std::ostream& os, const Map& map);

    /**
     * @brief Deserialize the Map object.
     *
     * This method deserializes the Map object from an input stream. It reads the map dimensions followed by the state of each cell in the map.
     *
     * @param is The input stream to deserialize the Map object from.
     * @param map The Map object to be deserialized.
     * @return A reference to the input stream after deserialization.
     */
    friend std::istream& operator>>(std::istream& is, Map& map);

    /**
     * @brief Update the start and end coordinates of the map.
     *
     * This method updates the start and end coordinates of the map based on the current state of the map cells. It iterates through the map to find the coordinates of the starting and ending points.
     */
    void updateStartAndEndCoordinates();

    /**
    * @brief Returns the width of the Map
    * @return width of map
    */
    int getWidth() const;

    /**
     * @brief Returns the height of the Map
     * @return height of map
     */
    int getHeight() const;

    /**
    * @brief Returns Object of a cell given the cooridnate
    * @param x
    * @param y
    * @return Cell - content of the cell
    */
    Cell* getCell(int x, int y);

    bool moveNextTo(Character *characterToMove, int distance);

    vector<Coordinate> findPathBFS(const Coordinate& start);

    vector<Character*> findAdjacentCharacters(Character* character);

    void removeCharacterFromMap(Character* character);

    vector <Character*> getAllCharacters();

    void attach(IObserver* observer) override;

    void detach(IObserver* observer) override;

    void notify(const std::string& message) override;

    /**
     * place a chest on the map
     */
    bool placeChest(ItemContainer *container,int x,int y);


    /**
     * Place Opponnent on the Map
     */
    bool placeOpponent(Character *character,int x,int y);

    /**
     * has User achieved all the objectives
     */
    Map* hasCompleted(Character *character);

    /**
     * can user go back to previous map
     */
    Map* goPreviousMap(Character *character);

    /**
     * Connect the Map to Another Map
     * @param map
     * @return
     */
    bool setNextMap(Map* map);

    /**
     * set previous map
     * @param map
     * @return
     */
     bool setPrevMap(Map* map);


     /**
      * Get all the ajacent itemContainer Present
      */
     std::map<string,ItemContainer*> getAdjacentChest(Character* character);


private:
    /**
     * A utility function used to determine if the coordinate is the Queue used in Breadth first search
     *
     * @param q1
     * @param c1
     * @return
     */
    static bool Contains(queue<Coordinate> q1,Coordinate &c1);

    /**
     * Takes Character Pointer and returns the Current Position Cell
     * @param c
     * @return
     */
    Cell* GetCurrentPositionCell(Character* c);

    /**
     * Takes Character Pointer and returns the Coordinate
     * @param c
     * @return
     */
     Coordinate getCurrentPosition(Character* c);

     /**
      * Takes Character pointer and moves it to move Position (X,Y)
      * @param c
      * @param x
      * @param y
      */
    bool move(Character* c,int x ,int y);





private:
    /**
     * No of enemies left on the map
     */
    int noOfEnemies;
    /**
     * Map which Open through the Exit
     */
    Map *nextMap;

    /**
     * the previous map in the compaign
     */
     Map *prevMap;
    /**
     *
     * Stores 2 dimensional Array
     */
    Cell** map;
    /**
     * Stores the Width of the array
     */
    int width;
    /**
     * Stores the Heigth of the array
     */
    int height;

    /**
     * Stores starting and ending coordinates of the Character
     */
    int startX,startY,endX,endY;

    /**
     * Stores the coordinates of the Player
     */
    int playerX,playerY;

    /**
     * Stores state which is been taken by the character
     */
    std::map<Character*, Coordinate> characterPositions;


    /**
     * list of observer
     */
    std::list<IObserver*> observers;

};


#endif //COMP345A1_MAP_H
