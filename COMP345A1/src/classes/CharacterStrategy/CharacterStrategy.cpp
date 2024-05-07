
#include "CharacterStrategy.h"

//--------------------HumanPlayerStrategy--------------------



void HumanPlayerStrategy::move(Character* c, Map* map){
    int input;
    map->printMap();
    int initialMap = c->currentMap;
    int moveDistance = 4 + c->getLevel();
    while (moveDistance > 0) {
        if (c->currentMap != initialMap){
            return;
        }
        cout << "\nChoose a movement option:" << endl;
        cout << "1: Up" << endl;
        cout << "2: Down" << endl;
        cout << "3: Left" << endl;
        cout << "4: Right" << endl;
        cout << "5: Stay at current position" << endl;
        cout << "You have " << moveDistance << " moves left." << endl;

        cout << "Enter option: ";
        cin >> input;

        switch (input) {
            case 1: {
                if (map->tryMove(c, "up")) {
                    moveDistance--;
                }
                break;
            }
            case 2: {
                if (map->tryMove(c, "down")) {
                    moveDistance--;
                }
                break;
            }
            case 3: {
                if (map->tryMove(c, "left")) {
                    moveDistance--;
                }
                break;
            }
            case 4: {
                if (map->tryMove(c, "right")) {
                    moveDistance--;
                }
                break;
            }
            case 5: {
                return;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
    }
}

void HumanPlayerStrategy::attack(Character* source, Map* map) {
    // Find adjacent enemies
    std::vector<Character*> adjacentEnemies = map->findAdjacentCharacters(source);

    if (adjacentEnemies.empty()) {
        std::cout << "No enemies nearby to attack." << std::endl;
        return; // Early return if no enemies are found
    }

    // Display enemies to user
    std::cout << "Select an enemy to attack (or select " << adjacentEnemies.size() + 1 << " to not attack):" << std::endl;
    for (size_t i = 0; i < adjacentEnemies.size(); ++i) {
        std::cout << i + 1 << ". " << adjacentEnemies[i]->getName() << std::endl; // Assuming Character has a getName() method
    }
    std::cout << adjacentEnemies.size() + 1 << ". Do not attack" << std::endl;

    // Get user input
    int choice = 0;
    std::cin >> choice;

    // Validate input (assumes choice is 1-indexed, plus one additional option to not attack)
    while (std::cin.fail() || choice < 1 || choice > adjacentEnemies.size() + 1) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line
        std::cout << "Invalid selection. Please try again: ";
        std::cin >> choice;
    }

    // Check if user chose not to attack
    if (choice == adjacentEnemies.size() + 1) {
        std::cout << "No attack this turn." << std::endl;
        return; // Early return if user chooses not to attack
    }

    // Adjust for 0-indexed vector
    Character* target = adjacentEnemies[choice - 1];

    // Attack selected target
    Dice dice;
    int damage = dice.roll("1d6"); // Roll for damage
    source->attack(target, damage); // Perform the attack
    if (target->hitPoints <= 0) {
        source->levelUp();
        int input;
        cout << "Do You want to search the Body : Input 0 to search the Body" << endl;
        cin >> input;
        if(input == 0){
            target->getEquipment()->itemPickupMenu(source);
        }
        cout << "Character Removed from the Map "<< endl;
        // Character has been defeated
        map->removeCharacterFromMap(target);
    }
}

void HumanPlayerStrategy::freeAction(Character* character,Map* map) {
    int input;

    while (true) {
        cout << "\nChoose a free action:" << endl;
        cout << "1: Open Chest" << endl;
        cout << "2: Search Body" << endl;
        cout << "3: Quit" << endl;
        cout << "Enter option: ";
        cin >> input;
        switch (input) {
            case 1: {
                pickupItemFromChest(character,map);
                break;
            }
            case 2: {
                cout << "If you do something to get revenge it means that more people suffer." << endl;
                break;
            }
            case 3: {
                return;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
    }
}


void HumanPlayerStrategy::pickupItemFromChest(Character* character,Map* map) {
    std::map<string,ItemContainer*> chests = map->getAdjacentChest(character);
    int input;

    while (true) {
        cout << "\nWhich direction you want to search Chest:" << endl;
        cout << "1: Up" << endl;
        cout << "2: Down" << endl;
        cout << "3: Right" << endl;
        cout << "4: Left" << endl;
        cout << "5: Quit" << endl;
        cout << "Enter option: ";
        cin >> input;

        // Checks the input
        switch (input) {
            case 1: {
                if(chests["Up"] != nullptr){
                    chests.at("Up")->itemPickupMenu(character);
                }
                else{
                    cout << "No chest Found";
                }
                break;
            }
            case 2: {
                if(chests["Down"] != nullptr){
                    chests.at("Down")->itemPickupMenu(character);
                }
                else{
                    cout << "No chest Found";
                }
                break;
            }
            case 3: {
                if(chests["Right"] != nullptr){
                    chests.at("Right")->itemPickupMenu(character);
                }
                else{
                    cout << "No chest Found";
                }
                break;
            }
            case 4: {
                if(chests["Left"] != nullptr){
                    chests.at("Left")->itemPickupMenu(character);
                }
                else{
                    cout << "No chest Found";
                }
                break;
            }
            case 5: {
                return;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
    }

}

//--------------------AggressorStrategy--------------------

void AggressorStrategy::move(Character* c, Map* map){
    map->printMap();
    int movementRange = 2 + c->getLevel();
    if (map->moveNextTo(c, movementRange)){
        cout << c->getName() << " advanced towards you." << endl;
    }
}

void AggressorStrategy::attack(Character* source, Map* map) {
    std::vector<Character*> adjacentEnemies = map->findAdjacentCharacters(source);
    Dice dice;
    for (Character* enemy : adjacentEnemies) {
        int damage = dice.roll("1d20"); // Roll for damage
        source->attack(enemy, damage);
        if (enemy->hitPoints <= 0) {
            cout << "\n\nYOU HAVE BEEN DEFEATED, GAME OVER!.\n";
            exit(0);
        }
    }
}


//--------------------FriendlyStrategy--------------------

void FriendlyStrategy::move(Character* c, Map* map){
    map->printMap();
    int movementRange = 2 + c->getLevel();
    if (map->moveNextTo(c, movementRange)){
        cout << c->getName() << " advanced towards you." << endl;
    }
}

void FriendlyStrategy::attack(Character* source, Map* map) {
    cout << "Hi, I'm friendly. But don't test the limits of my kindness." << endl;
}