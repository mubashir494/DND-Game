#include "MapEditor.h"
#include <sstream>
#include <fstream>


using namespace std;

MapEditor::MapEditor() : map(nullptr), campaign(nullptr) {} // Constructor initializes map and campaign pointers to nullptr

MapEditor::~MapEditor() {
    // Deallocate memory for map if it's not nullptr
    clearMap();
    clearCampaign();
}

void MapEditor::runEditor() {
    int input;

    while (true) {
        cout << "\nChoose an option:" << endl;
        cout << "1: Run map editor" << endl;
        cout << "2: Run campaign editor" << endl;
        cout << "3: Quit" << endl;
        cout << "Enter option: ";
        cin >> input;

        switch (input) {
            case 1: {
                runMapEditor();
                break;
            }
            case 2: {
                runCampaignEditor();
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

void MapEditor::runMapEditor() {
    int input;

    while (true) {
        cout << "\nChoose an option:" << endl;
        cout << "1: Create a new map" << endl;
        cout << "2: Load an existing map" << endl;
        cout << "3: Quit" << endl;
        cout << "Enter option: ";
        cin >> input;

        switch (input) {
            case 1: {
                createNewMap();
                break;
            }
            case 2: {
                loadMapFromFile();
                break;
            }
            case 3: {
                clearMap(); // Clear the current map if it exists
                return;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }

        // If map is not initialized, continue to the next iteration
        if (map == nullptr)
            continue;

        // If map is initialized, provide options to edit or save the map
        while (true) {
            cout << "\nChoose an option:" << endl;
            cout << "1: Edit map" << endl;
            cout << "2: Save map to file" << endl;
            cout << "3: Return to main menu" << endl;
            cout << "Enter option: ";
            cin >> input;

            switch (input) {
                case 1: {
                    editMap();
                    break;
                }
                case 2: {
                    if (map->isValid()) {
                        saveMapToFile();
                    } else {
                        cout << "\nThe map is invalid. Please edit the map to make it valid before saving." << endl;
                    }
                    break;
                }
                case 3: {
                    clearMap(); // Reset or clear the current map
                    break;
                }
                default: {
                    cout << "Invalid option. Please try again." << endl;
                    break;
                }
            }

            if (input == 3) // Return to main menu
                break;
        }
    }
}

Campaign* MapEditor::runCampaignEditor(string filename) {
    int input;

    while (true) {
        //handle when filename is not empty
        if(!filename.empty()){
            loadCampaignFromFile(filename);
            return campaign;
        }
        cout << "\nChoose an option:" << endl;
        cout << "1: Create a new campaign" << endl;
        cout << "2: Load an existing campaign" << endl;
        cout << "3: Quit" << endl;
        cout << "Enter option: ";
        cin >> input;

        switch (input) {
            case 1: {
                createNewCampaign();
                break;
            }
            case 2: {
                loadCampaignFromFile();
                break;
            }
            case 3: {
                clearCampaign(); // Clear the current campaign if it exists
                return nullptr;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }


        // If map is not initialized, continue to the next iteration
        if (campaign == nullptr)
            continue;


        // If map is initialized, provide options to edit or save the map
        while (true) {
            cout << "\nChoose an option:" << endl;
            cout << "1: Edit campaign" << endl;
            cout << "2: Save campaign to file" << endl;
            cout << "3: Go to player character creation" << endl;
            cout << "Enter option: ";
            cin >> input;

            switch (input) {
                case 1: {
                    editCampaign();
                    break;
                }
                case 2: {
                    if (campaign->isValid()) {
                        saveCampaignToFile();
                    } else {
                        cout << "\nThe map is invalid. Please edit the map to make it valid before saving." << endl;
                    }
                    break;
                }
                case 3: {
                    break;
                }
                default: {
                    cout << "Invalid option. Please try again." << endl;
                    break;
                }
            }

            if (input == 3) // Return to main menu
                break;
        }


        return campaign;
    }

}

void MapEditor::createNewMap() {
    clearMap(); // Clear the current map if it exists

    cout << "What size map would you like to create?" << endl;
    int mapWidth, mapHeight;
    cout << "Map width = ";
    cin >> mapWidth;
    cout << "Map height = ";
    cin >> mapHeight;

    map = new Map(mapWidth, mapHeight); // Dynamically allocate memory for map
    cout << mapWidth << "x" << mapHeight << " map created." << endl;
    map->printMap();
}

void MapEditor::editMap() {
    string input;
    while (input != "q") {
        cout << "To edit the map, enter coordinates (x,y) followed by the item:\n"
                "\t(x,y)item\n"
                "\n"
                "Items:\n"
                "\tS - Start point\n"
                "\tE - End point\n"
                "\t# - Wall\n"
                "\tD - Door\n"
                "\tO - Opponent\n"
                "\tC - Chest\n"
                "\t. - Empty cell\n"
                "\n"
                "Type 'q' to quit." << endl;
        cout << "Enter input: ";
        cin >> input;

        if (input == "q")
            break;

        // Parse input string to get coordinates and item
        int x, y;
        char item;
        if (parseInput(input, x, y, item)) {
            // Place or replace the item on the map
            if(item == 'C') {
                ItemContainer* container = new ItemContainer();
                ItemContainerEditor editor;
                editor.run(container);
                map->placeChest(container,x,y);
            }
            else if(item == 'O'){
                CharacterEditor characterEditor;
                Character* npc = characterEditor.runNpcEditor();
                if(npc != nullptr ){
                    map->placeOpponent(npc,x,y);
                    cout << "No Character was Created or Loaded" << endl;
                }

            }
            // Place or replace the item on the map
            map->Place(x, y, item);
            map->printMap();
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

bool MapEditor::parseInput(const string& input, int& x, int& y, char& item) {
    // Assuming input format is "(x,y)item"
    if (input.size() != 6 || input[0] != '(' || input[2] != ',' || input[4] != ')')
        return false;



    x = input[1] - '0';
    y = input[3] - '0';
    item = input[5];

    return true;
}

void MapEditor::saveMapToFile() {
    string filename;
    cout << "Enter filename to save the map: ";
    cin >> filename;

    filename += ".txt"; // Append .txt extension

    ofstream file(filename);
    if (file.is_open()) {
        file << *map; // Dereference the map pointer to access the Map object and serialize it
        cout << "Map saved to file: " << filename << endl;
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void MapEditor::loadMapFromFile() {
    clearMap(); // Clear the current map if it exists

    string filename;
    cout << "Enter filename to load the map (without the file extension): ";
    cin >> filename;

    filename += ".txt"; // Append .txt extension

    ifstream file(filename);
    if (file.is_open()) {
        // Dynamically allocate memory for map and deserialize the map from the file
        map = new Map(0, 0); // Initialize with default dimensions
        file >> *map;
        cout << "Map loaded from file: " << filename << endl;

        // Update startX, startY, endX, endY according to the loaded map
        map->updateStartAndEndCoordinates();

        // Check map validity
        if (map->isValid()) {
            map->printMap(); // Display the loaded map
        } else {
            cout << "Error: The map could not be loaded because it is invalid." << endl;
            clearMap(); // Clear the invalid map
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void MapEditor::clearMap() {
    if (map != nullptr) {
        delete map; // Clear the current map if it exists
        map = nullptr; // Reset the map pointer to nullptr
    }
}

void MapEditor::clearCampaign() {
    if (campaign != nullptr) {
        delete campaign; // Clear the current campaign if it exists
        campaign = nullptr; // Reset the campaign pointer to nullptr
    }
}

void MapEditor::createNewCampaign() {
    clearCampaign(); // Clear the current campaign if it exists

    cout << "Creating a new campaign." << endl;
    cout << "Enter initial width and height for the first map of your campaign:\n";
    int mapWidth, mapHeight;
    cout << "Map width = ";
    cin >> mapWidth;
    cout << "Map height = ";
    cin >> mapHeight;

    campaign = new Campaign(mapWidth, mapHeight);
    cout << "New campaign created." << endl;
    campaign->printCampaign();
}

void MapEditor::editCampaign() {
    if (campaign == nullptr) {
        cout << "No campaign exists to edit." << endl;
        return;
    }

    int mapIndex;
    while (true) {
        cout << "\nChoose a map to edit by entering it's map number\n"
                "0. Add a new map to the campaign\n"
                "-1. Return to previous menu\n"
                "Enter option: ";
        cin >> mapIndex;
        mapIndex--;

        if (mapIndex == -1) {
            addNewMapToCampaign();
        }
        else if (mapIndex == -2) {
            return;
        }
        else if (mapIndex >= 0 && mapIndex < campaign->getNumMaps()) {
            // Edit the selected map
            editMapInCampaign(mapIndex);
        } else {
            cout << "Invalid map index. Please try again." << endl;
        }
    }
}

void MapEditor::editMapInCampaign(int mapIndex) {
    Map* map = campaign->getMap(mapIndex);
    if (map == nullptr) {
        cout << "Error: Map not found." << endl;
        return;
    }

    cout << "Editing Map " << mapIndex + 1 << ":" << endl;
    map->printMap();

    string input;
    while (input != "q") {
        cout << "To edit the map, enter coordinates (x,y) followed by the item:\n"
                "\t(x,y)item\n"
                "\n"
                "Items:\n"
                "\tS - Start point\n"
                "\tE - Exit Door\n"
                "\t# - Wall\n"
                "\tD - Door\n"
                "\tO - Opponent\n"
                "\tC - Chest\n"
                "\t. - Empty cell\n"
                "\n"
                "Type 'q' to quit." << endl;
        cout << "Enter input: ";
        cin >> input;

        if (input == "q")
            break;

        // Parse input string to get coordinates and item
        int x, y;
        char item;
        if (parseInput(input, x, y, item)) {
            // Place or replace the item on the map
            if(item == 'C') {
                ItemContainer* container = new ItemContainer();
                ItemContainerEditor editor;
                editor.run(container);
                map->placeChest(container,x,y);
            }
            else if(item == 'O'){
                CharacterEditor characterEditor;
                Character* npc = characterEditor.runNpcEditor();

                if(npc != nullptr ){
                    map->placeOpponent(npc,x,y);
                }

            }
            else {
                map->Place(x, y, item);
            }

            map->printMap();
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

void MapEditor::saveCampaignToFile() {
    if (campaign == nullptr) {
        cout << "No campaign exists to save." << endl;
        return;
    }

    string filename;
    cout << "Enter filename to save the campaign: ";
    cin >> filename;
    filename += ".txt"; // Append .txt extension

    ofstream file(filename);
    if (file.is_open()) {
        file << *campaign;
        cout << "Campaign saved to file: " << filename << endl;
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void MapEditor::loadCampaignFromFile(string pregen) {
    clearCampaign(); // Clear the current campaign if it exists
    string filename;

    if(pregen.empty()){
        cout << "Enter filename to load the campaign (without the file extension): ";
        cin >> filename;

    }
    else{
        filename = pregen;
    }
    filename += ".txt"; // Append .txt extension
    ifstream file(filename);
    if (file.is_open()) {
        campaign = new Campaign(0, 0); // Initialize with default dimensions
        file >> *campaign;
        cout << "Campaign loaded from file: " << filename << endl;

        // Update start and end coordinates for all maps in the loaded campaign
        for (int i = 0; i < campaign->getNumMaps(); ++i) {
            Map* map = campaign->getMap(i);
            if (map) {
                map->updateStartAndEndCoordinates();
            } else {
                cout << "Error: Map at index " << i << " is null." << endl;
            }
        }

        for (int i = 0; i < campaign->getNumMaps(); ++i) {
            if (i > 0){
                campaign->maps[i]->setPrevMap(campaign->maps[i-1]);
            }
            if (i < campaign->getNumMaps() - 1) {
                campaign->maps[i]->setNextMap(campaign->maps[i+1]);
            }
        }

        // Check campaign validity
        if (!campaign->isValid()) {
            cout << "Error: The campaign could not be loaded because it contains invalid maps." << endl;
            clearCampaign(); // Clear the invalid campaign
        } else{
            campaign->printCampaign();
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void MapEditor::addNewMapToCampaign() {
    int choice;
    cout << "\nChoose an option:" << endl;
    cout << "1. Create a new map" << endl;
    cout << "2. Load a map from a file" << endl;
    cout << "Enter option: ";
    cin >> choice;

    if (choice == 1) {
        // Create a new map
        int width, height;
        cout << "Enter the dimensions of the new map which will be added to the campaign:" << endl;
        cout << "Map width = ";
        cin >> width;
        cout << "Map height = ";
        cin >> height;

        // Create a new map with the provided dimensions
        Map* newMap = new Map(width, height);

        // Add the new map to the campaign
        campaign->addMap(newMap);

        cout << "New map added to the campaign." << endl;
        campaign->printCampaign();

    } else if (choice == 2) {
        // Load a map from a file
        string filename;
        cout << "Enter filename to load the map: ";
        cin >> filename;

        ifstream file(filename);
        if (file.is_open()) {
            Map* loadedMap = new Map(0, 0); // Initialize with default dimensions
            file >> *loadedMap;
            file.close();

            loadedMap->updateStartAndEndCoordinates();

            // Check if the loaded map is valid
            if (loadedMap->isValid()) {
                // Add the loaded map to the campaign
                campaign->addMap(loadedMap);
                cout << "Map loaded from file and added to the campaign." << endl;
                campaign->printCampaign();
            } else {
                cout << "Error: The loaded map is not valid. Discarding it." << endl;
                delete loadedMap; // Discard the loaded map
            }
        } else {
            cout << "Error: Unable to open file." << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}