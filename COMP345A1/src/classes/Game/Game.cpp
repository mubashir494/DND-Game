//
// Created by hp on 01/04/2024.
//

#include "Game.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>

bool Game::getCampaign() {

    while (true) {
        int input;
        cout << "\nChoose an option:" << endl;
        cout << "1: Use Pre-generated Campaigns" << endl;
        cout << "2: Create/Load campaign" << endl;
        cout << "3: Continue to Character Creation" << endl;
        cout << "4: Quit" << endl;
        cout << "Enter option: ";
        cin >> input;

        switch (input) {
            case 1: {
                // TBD Load Pre-generated Campaign
                campaign =loadPregeneratedCampaign();
                break;
            }
            case 2: {
                MapEditor *mapEditor = new MapEditor();
                campaign = mapEditor->runCampaignEditor();
                return true;
            }
            case 3: {
                if(campaign == nullptr){
                    cout << "You haven't selected any Campaign Yet" << endl;
                    continue;
                }
                else{
                    return true;
                }

            }
            case 4 : {
                return false;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                continue;
            }
        }

    }
}



void Game::play()
{
    cout << "----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\tWelcome to the Dungeon and Dragon : Basic Fantasy RPG\n";
    cout << "----------------------------------------------------------------------------------------------";

    bool campaignSet = getCampaign();
    if(campaignSet){
        // ALL THE LOGIC OF SELECTING THE CHARACTER
        CharacterEditor characterEditor;
        Character* pCharacter = characterEditor.runCharacterEditor();
        if(pCharacter != nullptr){
            cout << "\n\n----------------------------------------------------------------------------------------------\n";
            cout << "\t\t\t\t\t\t\t\t\t\tWELCOME TO DND WORLD\n";
            cout << "----------------------------------------------------------------------------------------------\n\n";

            cout << "\tTHE GAME RULES:\n";

            cout << "Objective:\n"
                      << " - Defeat all enemies on each level to unlock the door to the next level.\n"
                      << " - Clear all levels to win the game.\n\n";

            cout << "Gameplay Mechanics:\n"
                      << " - Character Setup: You control a single player character.\n"
                      << " - Levels: Progress through each level by defeating all enemies to unlock the next level.\n"
                      << " - Dice Rolls: Each round begins with a dice roll to determine the turn order for all characters on the map.\n"
                      << " - Movement: Move your character around the map each turn.\n"
                      << " - Attack: Engage enemies in combat when they are within range.\n"
                      << " - Interactions:\n"
                      << "     - Open chests to find items.\n"
                      << "     - Pick up items dropped by defeated enemies.\n"
                      << "     - Access your inventory to switch equipped items or use items.\n"
                      << " - Enemy Behavior: Enemies will move towards your character and may attack if you are within their attack range.\n\n";

            cout << "Progression and Leveling:\n"
                      << " - Experience and Leveling:\n"
                      << "     - Gain experience and level up by defeating enemies.\n"
                      << "     - Leveling up improves your character’s strength and increases health points (HP).\n"
                      << " - Inventory Management:\n"
                      << "     - Manage your inventory to optimize equipment and item usage.\n"
                      << "     - Utilize dropped items from enemies to enhance your character's capabilities.\n\n";

            cout << "Winning and Losing:\n"
                      << " - Winning the Game: Successfully clear all campaign levels to win the game.\n"
                      << " - Losing the Game: If your character dies, it's game over, and you must start over from the beginning.\n\n";

            cout << "Tips for Success:\n"
                      << " - Plan your moves and attacks strategically.\n"
                      << " - Keep an eye on your health.\n"
                      << " - Regularly update and manage your equipment to match your play style and challenges.\n"
                      << " - Learn enemy patterns to anticipate attacks and counter effectively.\n\n";

            cout << "Enjoy the game and good luck!\n\n";

            bool gameIsRunning = true;
            campaign->printCampaign();
            campaign->maps[pCharacter->currentMap]->placeCharacter(pCharacter);
                while(gameIsRunning){
                    campaign->maps[pCharacter->currentMap]->getAllCharacters();
                    vector<Character*> characters = campaign->maps[pCharacter->currentMap]->getAllCharacters();
                    characters = initiativeRoll(characters);
                    for(auto* character : characters) {
                        cout << "\n---------------------------------------------" << endl;
                        cout << "\t\t\t" <<character->getName() << "'s play turn" << endl;
                        cout << "---------------------------------------------" << endl;
                        if (character->strategy->getStrategyType() == "Human"){
                            bool playerTurn = true;
                            bool moved = false;
                            bool attacked = false;
                            while (playerTurn) {
                                int input;
                                cout << "\nChoose an option:" << endl;
                                cout << "1: Move" << endl;
                                cout << "2: Attack" << endl;
                                cout << "3: Perform Loot Action" << endl;
                                cout << "4: Items Inventory" << endl;
                                cout << "5: Check Your Character Sheet"<< endl;
                                cout << "6: End Turn" << endl;
                                cout << "Enter option: ";
                                cin >> input;

                                switch (input) {
                                    case 1: {
                                        if (!moved) {
                                            character->move(campaign->maps[pCharacter->currentMap]);
                                            moved = true;
                                        }
                                        else{
                                            cout << "You have already moved this round.\n";
                                        }
                                        break;
                                    }
                                    case 2: {
                                        if (!attacked) {
                                            character->attack(campaign->maps[pCharacter->currentMap]);
                                            attacked = true;
                                        }
                                        else{
                                            cout << "You have already attacked this round.\n";
                                        }
                                        break;
                                    }
                                    case 3: {
                                        character->freeAction(campaign->maps[pCharacter->currentMap]);
                                        break;
                                    }
                                    case 4 : {
                                        characterEditor.updateWornItemEditor(pCharacter);
                                        break;
                                    }
                                    case 5 : {
                                        character->displayCharacterSheet();
                                        break;
                                    }
                                    case 6: {

                                        playerTurn = false;
                                        break;
                                    }
                                    default: {
                                        cout << "Invalid option. Please try again." << endl;
                                        continue;
                                    }
                                }
                            }
                        }
                        else{
                            character->move(campaign->maps[pCharacter->currentMap]);
                            character->attack(campaign->maps[pCharacter->currentMap]);
                        }
                    }
                }
        }
    }
    else{
        cout << "Thank you for Playing !";
    }
}

Campaign* Game::loadPregeneratedCampaign() {

    while (true){
        int input;
        cout << "\nChoose the Campaign You want to Play: -1 to exit" << endl;
        cout << "1: The Kingdoms of Thaloria" << endl;
        cout << "2: The Impossible Single Dungeon" << endl;
        cout << "3: The Tales of the White Dragon" << endl;
        cout << "4: The Double Trouble" << endl;
        cout << "5: ??? RANDOM MAP ???" << endl;
        cout << "Enter Option: ";
        cin >>input;
        cout << endl;
        if (input == 5){
            srand(time(0)); // Use current time as seed for random generator
            input = 1 + rand() % 4; // rand() % 3 gives a range of 0 to 2; adding 1 changes it to 1 to 3
        }
        switch (input) {
            case 1 : {
                MapEditor* mapEditor = new MapEditor();
                Campaign* camp = mapEditor->runCampaignEditor("pre-generated");
                return camp;
            }
            case 2 : {
                MapEditor* mapEditor = new MapEditor();
                Campaign* camp = mapEditor->runCampaignEditor("pre-generated2");
                return camp;
            }
            case 3 : {
                MapEditor* mapEditor = new MapEditor();
                Campaign* camp = mapEditor->runCampaignEditor("pre-generated3");
                return camp;
            }
            case 4 : {
                MapEditor* mapEditor = new MapEditor();
                Campaign* camp = mapEditor->runCampaignEditor("pre-gen2");
                return camp;
            }
            case -1 : {
                return nullptr;
            }
            default: {
                cout << "Error";
                continue;
            };
        }


    }
    return nullptr ;
}

vector<Character*> Game::initiativeRoll(vector<Character*> chars) {
    cout << "\n========================= STARTING NEW ROUND =========================\n";

    cout << "\n\tInitiative dice roll to determine turn order..." << endl;

    std::map<int,Character*> map ;
    vector<Character*> sorted_array;
    Dice dice;
    for(auto & i : chars){
        map[dice.roll("1d20")] =i ;
    }

    for (auto it = map.rbegin(); it != map.rend(); ++it) {
        sorted_array.push_back(it->second);
    }

    cout << "\tThis round's turn order = ";
    std::string separator = "";
    for(auto & i : sorted_array){
     cout << separator << i->getName();
        separator = ", ";
    }
    return sorted_array;

}
