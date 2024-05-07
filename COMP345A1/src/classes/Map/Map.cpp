//
// Created by hp on 12/02/2024.
//

#include "Map.h"
#include <cstdlib>

using namespace std;

Map::Map(int widthX, int heightY) {

    width = widthX;
    height = heightY;
    // Initialize Values to -1
    startX = -1;
    startY = -1;
    endX = -1;
    endY = -1;
    playerX = -1;
    playerY = -1;


    map =new Cell*[width];


    // Initialize the Map
    for(int i =0 ;i<width;i++){
        map[i] = new Cell[height];
    }

    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            map[x][y] = Cell(Cell::State::EMPTY, nullptr);
        }
    }

    // Set Up walls
    for (int i = 0;i<width;i++){
        map[i][0].setState(Cell::State::WALL, nullptr);
        map[i][height - 1].setState(Cell::State::WALL, nullptr);
    }
    for (int i =0;i<height;i++){
        map[0][i].setState(Cell::State::WALL, nullptr);
        map[width -1][i].setState(Cell::State::WALL, nullptr);
    }

    nextMap = nullptr;
    prevMap = nullptr;


    noOfEnemies = 0;
}






bool Map::Place(int x, int y, char item) {
    // Check if the coordinates are not Out of the Map
    if(x < 0 && x > width - 1 || y < 0 && y > height - 1){
        cout << "Coordinates are out of the Map" << endl;
        return false;
    }
    // Check if it is trying to replace Edges
    if ((x == 0 || x == width - 1) && (y == 0 || y == height -1)){
        cout << "You cant replace the wall" << endl;
        return false;
    }


    // If Placing Start
    if(item  == 'S'){
        cout << "Successfully Placed the Starting point" <<  endl;
        map[x][y].setState(Cell::State::START, nullptr);
        startX = x;
        startY = y;
        return true;
    }
    // If Placing Exit
    if(item == 'E') {
        cout << "Successfully set exit" << endl;
        map[x][y].setState(Cell::State::EXIT, nullptr);
        endX = x;
        endY = y;
        return  true;
    }

    // Can only place Door and wall at the edge of the Map
    if((x == 0 || x == width-1) || (y == 0 || y == height-1 )){

        if(item == '#'){
            if(startX == x && startY == y){
                startX = -1;
                startY = -1;
            }
            else if (endX == x && endY == y){
                endX = -1;
                endY = -1;
            }

            map[x][y].setState(Cell::State::WALL, nullptr);
            cout << "Successfully Placed the Wall" << endl;
            return true;

        }
        else if (item == 'D'){
            // Check if door is placed at the start position
            if(startX == x && startY == y){
                startX = -1;
                startY = -1;
            }
                // Check if door is placed at the Exit position
            else if(endX == x && endY == y) {
                endX = -1;
                endY = -1;
            }
            cout << "Successfully Placed the Door" << endl;
            map[x][y].setState(Cell::State::DOOR, nullptr);
            return true;

        }
        else{
            cout << "Invalid ! You can only place wall ,Starting point, ending point on the wall " << endl;
            return false;
        }
    }
    if(item  == '#'){
        if(startX == x && startY == y){
            startX = -1;
            startY = -1;
        }
            // Check if door is placed at the Exit position
        else if(endX == x && endY == y) {
            endX = -1;
            endY = -1;
        }
        cout << "Successfully Placed the Wall" << endl;
        map[x][y].setState(Cell::State::WALL, nullptr);
        return true;
    }

    if(item  == '.'){
        if(startX == x && startY == y){
            startX = -1;
            startY = -1;
        }
            // Check if door is placed at the Exit position
        else if(endX == x && endY == y) {
            endX = -1;
            endY = -1;
        }
        cout << "Successfully Emptied the Cell" << endl;
        map[x][y].setState(Cell::State::EMPTY, nullptr);
        return true;
    }

    if(item == 'O'){
        if(startX == x && startY == y){
            startX = -1;
            startY = -1;
        }
            // Check if door is placed at the Exit position
        else if(endX == x && endY == y) {
            endX = -1;
            endY = -1;
        }
        cout << "Successfully Placed the Opponent";
        map[x][y].setState(Cell::State::OPPONENT, nullptr);
        return true;

    }

    if(item == 'C'){
        if(startX == x && startY == y){
            startX = -1;
            startY = -1;
        }
            // Check if door is placed at the Exit position
        else if(endX == x && endY == y) {
            endX = -1;
            endY = -1;
        }
        cout << "Successfully Placed the Chest";
        map[x][y].setState(Cell::State::CHEST, nullptr);
        return true;

    }
    cout << "Invalid Inputs";
    return false;
}




// Apply BFS to find the Route from Starting to the End
bool Map::isValid() {
    // Check if we have start and End point on the Map
    if(startX == -1 || startY == -1 || endX == -1  || endY == -1 ){
        cout << "You must have one Start and End Cell";
        return false;
    }
    // Create a queue of Not Visited Nodes
    queue<Coordinate> notVisited;

    // Create a queue of Visited Notes
    queue<Coordinate> visited;

    // Create Coordinate of End
    Coordinate end =  {endX,endY};

    //Create Coordinate to be pushed on the Queue
    Coordinate c1 = {startX,startY};

    // Push the First Coordinate on the Not Visited Queue
    notVisited.push(c1);

    // Loop through until the queue is Empty
    while(!notVisited.empty()){
        // Pop the first Coordinate
        Coordinate &c2 = notVisited.front();
        notVisited.pop();

        // Push the Coordinate to the Visited Queue
        visited.push(c2);

        // Check if the Popped Coordinate is the Result
        if(c2.equalCoordinates(end)){
            //cout << "Map is valid" << endl;
            return true;
        }
        // If not then Explore all the Nodes
        else {
            // Walk towards Right
            if(c2.x + 1 < width && !map[c2.x + 1][c2.y].isWall() ){
                Coordinate c = {c2.x + 1,c2.y};
                // Check if it is not in both the Queues
                if(!Contains(notVisited,c) && !Contains(visited,c)){
                    notVisited.push(c);
                }
            }

            // Walk towards Left
            if(c2.x - 1 >= 0 && !map[c2.x -1][c2.y].isWall()){
                Coordinate c = {c2.x-1,c2.y};
                // Check if it is not in both the Queues
                if(!Contains(notVisited,c) && !Contains(visited,c)){
                    notVisited.push(c);
                }

            }

            // Walk Down
            if(c2.y + 1 < height && !map[c2.x][c2.y + 1].isWall()){
                Coordinate c = {c2.x,c2.y + 1};
                // Check if it is not in both the Queues
                if(!Contains(notVisited,c) && !Contains(visited,c)){
                    notVisited.push(c);
                }
            }
            // Walk up
            if(c2.y - 1 >= 0 && !map[c2.x][c2.y - 1].isWall()){
                Coordinate c = {c2.x,c2.y - 1};
                // Check if it is not in both the Queues
                if(!Contains(notVisited,c) && !Contains(visited,c)){
                    notVisited.push(c);
                }
            }

        }
    }
    // If the While Loop finishes without Returning then throw an error and return false
    cout << "Invalid Map ! No Route from starting to ending point" << endl;
    return false;
}

/**
 * Prints the Map
 */
void Map::printMap() {
    cout << "------------------------------------------------------------------------------------------" << endl;
    for (int j = height - 1; j >= 0; j--) {
        cout << "\t\t" << j << "\t";
        for (int i = 0; i < width; i++) {
            if (map[i][j].getState() == Cell::State::CHARACTER) {
                cout << map[i][j].getCharacter()->getName()[0] << " ";
            } else if (map[i][j].getState() == Cell::State::WALL) {
                cout << "# ";
            } else if (map[i][j].getState() == Cell::State::EMPTY) {
                cout << ". ";
            } else if (map[i][j].getState() == Cell::State::START) {
                cout << "S ";
            } else if (map[i][j].getState() == Cell::State::EXIT) {
                cout << "D ";
            } else if (map[i][j].getState() == Cell::State::OPPONENT) {
                cout << "O ";
            } else if (map[i][j].getState() == Cell::State::CHEST) {
                cout << "C ";
            } else if (map[i][j].getState() == Cell::State::DOOR) {
                cout << "D ";
            }
        }
        cout << endl;
    }
    cout << "\t\t\t";
    for (int i = 0; i < width; i++) {
        cout << i << " ";
    }
    cout << "\n------------------------------------------------------------------------------------------" << endl;
}

Map::~Map() {
    // Loop through the 2d array to delete each array
    for (int i = 0; i < height; ++i)
    {
        delete[] map[i];
    }
    delete map;
}

// Checks if the Coordinate is in the given Queue
bool Map::Contains(queue<Coordinate> q1, Coordinate &c1) {
    // Run until Queue is not Empty
    while(!q1.empty()){
        // Check and If found then return
        if(q1.front().equalCoordinates(c1))
            return true;
        // Pop the Coordinate
        q1.pop();
    }
    // Return False if no match is found
    return false;
}

bool Map::placeCharacter(Character *c) {
    // Check if the specified starting coordinates are within the map boundaries
    if (startX == -1 || startY == -1) {
        cout << "Error: No specified starting coordinates" << endl;
        return false;
    }

    // Check if the specified starting cell is empty
    if (map[startX][startY].getState() != Cell::State::START) {
        cout << "Error: Starting coordinates is not a START cell" << endl;
        return false;
    }

    // Place the character at the specified starting position
    map[startX][startY].setState(Cell::State::CHARACTER, c);
    characterPositions[c] = {startX, startY}; // Update character position

    noOfEnemies = getAllCharacters().size() - 1;

    notify("Starting level for " + c->getName() + " at (" + std::to_string(startX) + "," + std::to_string(startY) + ")");
    return true;
}

bool Map::placeNPC(Character *npc, int startingX, int startingY) {
    // Check if the specified starting coordinates are within the map boundaries
    if (startingX < 0 || startingX >= width || startingY < 0 || startingY >= height) {
        cout << "Error: Specified NPC starting coordinates are out of the map boundaries" << endl;
        return false;
    }

    // Check if the specified starting cell is empty
    if (map[startingX][startingY].getState() != Cell::State::EMPTY) {
        cout << "Error: Specified NPC starting coordinates are occupied" << endl;
        return false;
    }

    // Place the character at the specified starting position
    map[startingX][startingY].setState(Cell::State::CHARACTER, npc);
    characterPositions[npc] = {startingX, startingY}; // Update character position

    notify("Successfully placed npc " + npc->getName() + " at (" + std::to_string(startX) + "," + std::to_string(startY) + ")");
    return true;
}


bool Map::move(Character *c, int x, int y) {
    auto it = characterPositions.find(c);
    if (it != characterPositions.end()) {
        // Get the current position of the character
        Coordinate currentPos = it->second;

        // Update the cell state
        if (map[currentPos.x][currentPos.y].getState() == Cell::State::CHARACTER) {
            map[x][y].setState(Cell::State::CHARACTER, c);
        } else {
            map[x][y].setState(Cell::State::OPPONENT, c);
        }
        map[currentPos.x][currentPos.y].setState(Cell::State::EMPTY, nullptr);

        if (currentPos.x == startX && currentPos.y == startY){
            map[startX][startY].setState(Cell::State::START, nullptr);
        }

        if (currentPos.x == endX && currentPos.y == endY){
            map[endX][endY].setState(Cell::State::EXIT, nullptr);
        }

        // Update character position
        characterPositions[c] = {x, y};
        if (!hasCompleted(c)){
            printMap();
        }

        notify("Successfully moved character " + c->getName() + " to (" + std::to_string(x) + "," + std::to_string(y) + ")");
        return true;
    }
    cout << "Character not found on the map" << endl;
    return false;
}

bool Map::tryMove(Character *c, string dir) {
    auto it = characterPositions.find(c);
    if (it != characterPositions.end()) {
        Coordinate currentPos = it->second;

        // Calculate the new position based on the direction
        int x = currentPos.x, y = currentPos.y;

        if (dir == "up") {
            if (y + 1 < height && map[x][y + 1].canMove()) {
                y += 1;
            } else {
                cout << "Invalid move: outside map bounds or blocked." << endl;
                return false;
            }
        } else if (dir == "down") {
            if (y - 1 >= 0 && map[x][y - 1].canMove()) {
                y -= 1;
            } else {
                cout << "Invalid move: outside map bounds or blocked." << endl;
                return false;
            }
        } else if (dir == "right") {
            if (x + 1 < width && map[x + 1][y].canMove()) {
                x += 1;
            } else {
                cout << "Invalid move: outside map bounds or blocked." << endl;
                return false;
            }
        } else if (dir == "left") {
            if (x - 1 >= 0 && map[x - 1][y].canMove()) {
                x -= 1;
            } else {
                cout << "Invalid move: outside map bounds or blocked." << endl;
                return false;
            }
        } else {
            cout << "Invalid direction" << endl;
            return false;
        }

        // Attempt to move the character to the new position
        return move(c, x, y);
    }
    cout << "Character not found on the map" << endl;
    return false;
}


Coordinate Map::getCurrentPosition(Character *c) {
    auto it = characterPositions.find(c);
    if (it != characterPositions.end()) {
        return it->second;
    }
    return {-1, -1}; // Character not found
}

// Serialization method for Map
std::ostream& operator<<(std::ostream& os, const Map& map) {
    os << map.width << " " << map.height << " "; // Serialize map dimensions
    os << map.noOfEnemies << " ";
    // Serialize each cell in the map
    for (int i = 0; i < map.width; ++i) {
        for (int j = 0; j < map.height; ++j) {
            os << map.map[i][j]; // Serialize cell
        }
    }
    return os;
}

// Deserialization method for Map
std::istream& operator>>(std::istream& is, Map& map) {
    is >> map.width >> map.height; // Deserialize map dimensions
    // Resize map
    is >> map.noOfEnemies;
    map.map = new Cell*[map.width];
    for (int i = 0; i < map.width; ++i) {
        map.map[i] = new Cell[map.height];
    }
    string empty;
    // Deserialize each cell in the map
    for (int i = 0; i < map.width; ++i) {
        for (int j = 0; j < map.height; ++j) {
            is >> map.map[i][j]; // Deserialize cell
            if(map.map[i][j].getState() == Cell::State::OPPONENT || map.map[i][j].getState() == Cell::State::CHARACTER ){
                map.characterPositions[map.map[i][j].getCharacter()] = {i,j};
            }
        }
    }

    return is;
}

//When a map is loaded, it updates the start and exit coordinates
void Map::updateStartAndEndCoordinates() {
    // Loop through the map to find the coordinates of start and end points
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (map[x][y].getState() == Cell::State::START) {
                startX = x;
                startY = y;
            } else if (map[x][y].getState() == Cell::State::EXIT) {
                endX = x;
                endY = y;
            }
        }
    }
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

Cell *Map::getCell(int x, int y) {
    return &map[x][y];
}

vector<Coordinate> Map::findPathBFS(const Coordinate& start) {
    Coordinate target(-1, -1);
    vector<vector<bool>> visited(width, vector<bool>(height, false));
    queue<pair<Coordinate, vector<Coordinate>>> q;

    // Find the target character's location during the BFS initialization
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (map[x][y].getState() == Cell::State::CHARACTER && !(x == start.x && y == start.y)) {
                target = Coordinate(x, y); // Found the target character
                goto foundTarget; // Use goto for simplicity, to break out of nested loop
            }
        }
    }
    foundTarget:
    // Early exit if no target character was found
    if (target.x == -1) {
        cout << "No character found on the map." << endl;
        return {};
    }

    q.push({start, {start}}); // Start position included in initial path for clarity
    visited[start.x][start.y] = true;

    vector<Coordinate> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // Cardinal directions

    while (!q.empty()) {
        auto front = q.front(); q.pop();
        Coordinate currentPos = front.first;
        vector<Coordinate> path = front.second;

        // Check if the current position is next to a character
        for (const auto& dir : directions) {
            int adjacentX = currentPos.x + dir.x;
            int adjacentY = currentPos.y + dir.y;

            if (adjacentX >= 0 && adjacentX < width && adjacentY >= 0 && adjacentY < height) {
                if (map[adjacentX][adjacentY].getState() == Cell::State::CHARACTER) {
                    return path; // Return the current path if next to a character
                }
            }
        }

        // Explore only cardinal neighbors
        for (const auto& dir : directions) {
            int newX = currentPos.x + dir.x;
            int newY = currentPos.y + dir.y;

            if (newX >= 0 && newX < width && newY >= 0 && newY < height && !visited[newX][newY] && map[newX][newY].getState() == Cell::State::EMPTY) {
                visited[newX][newY] = true;
                vector<Coordinate> newPath = path;
                newPath.push_back(Coordinate(newX, newY)); // Add the new position to the path
                q.push({Coordinate(newX, newY), newPath});
            }
        }
    }

    cout << "Character is unreachable or no space next to character." << endl;
    return {}; // Return empty path if the target is unreachable or there's no space next to the character
}


// Move a character next to the first character found on the map
bool Map::moveNextTo(Character *characterToMove, int distance) {

    Coordinate currentCoord = getCurrentPosition(characterToMove);

    if (currentCoord.x == -1) {
        cout << "Error: Character not found on the map." << endl;
        return false;
    }

    std::vector<Coordinate> path = findPathBFS(currentCoord);
    if (path.empty()) {
        cout << "No path to any character found." << endl;
        return false;
    }

    // Ensure we don't try to move beyond the available path
    // -1 to ensure we stop before moving onto the CHARACTER cell itself
    int moveSteps = std::min(distance, static_cast<int>(path.size()));

    // Correcting an off-by-one error by adjusting moveSteps to properly index into the path
    // Given the path includes the start cell, we need to account for this in our indexing
    moveSteps = std::max(0, moveSteps - 1); // Ensure moveSteps is not negative

    Coordinate targetCoord = path[moveSteps];

    // Perform the move if the target position is different from the current position
    if (!(targetCoord.x == currentCoord.x && targetCoord.y == currentCoord.y)) {
        return move(characterToMove, targetCoord.x, targetCoord.y);
    }
    return false; // If the target position is the current position, treat as successful move
}

// Method to find characters adjacent to the given character's position
std::vector<Character*> Map::findAdjacentCharacters(Character* character) {
    std::vector<Character*> adjacentCharacters;

    Coordinate pos = getCurrentPosition(character);

    if (pos.x == -1 && pos.y == -1) {
        std::cout << "Character not found on the map." << std::endl;
        return adjacentCharacters;
    }

    int radius = 1; // Default radius for melee weapons
    auto weapon = character->getWeapon();
    if (weapon && weapon->getWeaponType() == Weapon::WeaponType::BOW) {
        radius = 5; // Larger radius for bow
    }

    // Check positions within the defined radius
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            if (dx == 0 && dy == 0) continue; // Skip the character's own position

            int newX = pos.x + dx;
            int newY = pos.y + dy;

            // Check boundaries
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                Cell& cell = *getCell(newX, newY);
                if (map[pos.x][pos.y].getState() == Cell::State::CHARACTER){
                    if (cell.getState() == Cell::State::OPPONENT && cell.getCharacter() != nullptr) {
                        adjacentCharacters.push_back(cell.getCharacter());
                    }
                }
                else if (map[pos.x][pos.y].getState() == Cell::State::OPPONENT){
                    if (cell.getState() == Cell::State::CHARACTER && cell.getCharacter() != nullptr) {
                        adjacentCharacters.push_back(cell.getCharacter());
                    }
                }
            }
        }
    }

    return adjacentCharacters;
}

void Map::attach(IObserver* observer) {
    observers.push_back(observer);
}

void Map::detach(IObserver* observer) {
    observers.remove(observer);
}

void Map::notify(const std::string& message) {
    if (loggingEnabled){
        for(auto observer : observers) {
            observer->update(message);
        }
    }
}


// takes map as input and set it as next map
bool Map::setNextMap(Map *map) {
    if(endX != -1 && endY != -1 ){
        nextMap = map;
        return true;
    }
    return false;
}
// take map as input and set it as previous map
bool Map::setPrevMap(Map *map) {
    if(startX != -1 && startY != -1 ){
        prevMap = map;
        return true;
    }
    return false;
}

Map* Map::hasCompleted(Character *character) {
    Coordinate c = getCurrentPosition(character);

    if (c.x == endX && c.y == endY){
        if (noOfEnemies == 0) {
            cout << "Congartulations! You have successfully cleared the dungeon.\n";
            if (nextMap != nullptr) {
                cout << "You are now entering the next dungeon level.\n";
                nextMap->placeCharacter(character);
                nextMap->printMap();
                character->currentMap++;
                return nextMap;
            } else{
                cout << "\n\nCONGRATULATIONS BRAVE WARRIOR! YOU HAVE WON THE GAME!.\n";
                exit(0);
            }
        } else {
            cout << "There are still enemies to kill. Destroy them and the exit might open.\n";
        }
    }

    // Check if the target position is within the map boundaries and empty
    return nullptr;
}

Map* Map::goPreviousMap(Character *character){
    Coordinate c = getCurrentPosition(character);
    vector<Coordinate> list = {Coordinate {c.x +1,c.y},Coordinate {c.x -1,c.y}, Coordinate{c.x,c.y +1},Coordinate {c.x,c.y -1 }};
    for(auto & i : list){
        if (i.x >= 0 && i.x < width && i.y >= 0 && i.y < height) {
            if (c.x == i.x && c.y == i.y) {
                // Change the location
                map[c.x][c.y].setState(Cell::State::EMPTY, nullptr);
                return prevMap;
            }
        }
    }
    // Check if the target position is within the map boundaries and empty
    return nullptr;
}


bool Map::placeOpponent(Character *character,int x,int y) {
    if(x < 0 && x > width - 1 || y < 0 && y > height - 1){
        cout << "The input Coordinates are out of bound";
        return false;
    }
    if(map[x][y].isEmpty()){
        characterPositions[character] = {x,y};
        map[x][y].setState(Cell::State::OPPONENT,character);

        noOfEnemies ++;
        return true;
    }
    return false;
}

vector<Character*> Map::getAllCharacters() {
    vector<Character*> list;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if(map[x][y].getState() == Cell::CHARACTER || map[x][y].getState() == Cell::OPPONENT){
                list.push_back(map[x][y].getCharacter());
            }
        }
    }
    return list;
}

bool Map::placeChest(ItemContainer *container, int x, int y) {
    if(x < 0 && x > width - 1 || y < 0 && y > height - 1){
        cout << "The input Coordinates are out of bound";
        return false;
    }
    if(map[x][y].isEmpty()){
        map[x][y].setState(Cell::State::CHEST,container);
        return true;
    }
    return false;

}

void Map::removeCharacterFromMap(Character *character) {
    auto it = characterPositions.find(character);
    if (it != characterPositions.end()) {
        map[it->second.x][it->second.y].setState(Cell::State::EMPTY, nullptr);
        characterPositions.erase(it);
        noOfEnemies--;
        cout << "You have defeated: " <<  character->getName()  <<  endl;
    }
}
std::map<string,ItemContainer*> Map::getAdjacentChest(Character* character){
    std::map<string,ItemContainer*> adjacentChest;
    Coordinate c1 = getCurrentPosition(character);
    // check for adjacent cells for the chest;
    if (c1.x == -1 && c1.y == -1) {
        std::cout << "Character not not found on the map." << std::endl;
        return adjacentChest; // Character is not on the map
    }
    // Check all eight adjacent positions
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            // Skip the character's current position
            if (dx == 0 && dy == 0) continue;

            int newX = c1.x + dx;
            int newY = c1.y + dy;
            // Check boundaries
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                Cell& cell = *getCell(newX, newY);
                // If there's a character in the cell, add it to the list
                if (map[newX][newY].getState() == Cell::State::CHEST){

                    if(newX == c1.x + 1 && newY == c1.y ){
                        cout << "chest found";
                        adjacentChest["Right"] = map[newX][newY].getChest();
                    }
                    if(newX == c1.x - 1 && newY == c1.y ){
                        cout << "chest found";
                        adjacentChest["Left"] = map[newX][newY].getChest();
                    }
                    if(newX == c1.x  && newY == c1.y + 1){
                        adjacentChest["Up"] = map[newX][newY].getChest();
                    }
                    if(newX == c1.x && newY == c1.y -1 ){
                        adjacentChest["Down"] = map[newX][newY].getChest();
                    }
                }

            }
        }
    }
    return adjacentChest;
}