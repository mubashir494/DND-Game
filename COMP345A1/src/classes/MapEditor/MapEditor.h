#ifndef COMP345A1_MAPEDITOR_H
#define COMP345A1_MAPEDITOR_H

#include <iostream>
#include "../Map/Map.h"
#include "../Campaign/Campaign.h"
#include "../ItemContainerEditor/ItemContainerEditor.h"
#include "../CharacterEditor/CharacterEditor.h"

/**
 * @brief Represents a map editor for a simple d20 game.
 *
 * The MapEditor class provides functionality to create, edit, and save maps as well as campaigns.
 * It allows users to interactively modify maps and campaigns through a command-line interface.
 *
 * Game Rules:
 * - Users can create, edit, and save individual maps or entire campaigns.
 * - Maps consist of various elements such as walls, doors, opponents, chests, and empty cells.
 * - Campaigns are composed of multiple interconnected maps.
 *
 * Class Design:
 * - MapEditor class facilitates interactive map and campaign editing.
 * - Uses Map and Campaign classes for managing individual maps and campaigns, respectively.
 * - Provides options to create new maps, load existing maps, edit maps, and save maps to files.
 *
 * Library Selection Rationale:
 * - iostream: Standard Input/Output Stream Library for handling console input/output.
 * - sstream: Used for string manipulation to parse user input.
 * - fstream: Required for file input/output operations, essential for saving/loading maps and campaigns.
 */
class MapEditor {
public:
    /**
     * @brief Constructor for the MapEditor class.
     */
    MapEditor();

    /**
     * @brief Destructor for the MapEditor class.
     */
    ~MapEditor();

    /**
     * @brief Runs the map editor application.
     *
     * Provides a menu-driven interface for users to choose between map editor and campaign editor.
     */
    void runEditor();

    /**
     * @brief Runs the map editor functionality.
     *
     * Allows users to create, load, edit, and save individual maps.
     */
    void runMapEditor();

    /**
     * @brief Runs the campaign editor functionality.
     *
     * Allows users to create, load, edit, and save campaigns consisting of multiple maps.
     */
    Campaign* runCampaignEditor(string filename="");

private:
    Map* map; ///< Pointer to a Map object for current editing.
    Campaign* campaign; ///< Pointer to a Campaign object for current editing.

    /**
     * @brief Creates a new map based on user input.
     */
    void createNewMap();

    /**
     * @brief Creates a new campaign based on user input.
     */
    void createNewCampaign();

    /**
     * @brief Edits the current map interactively.
     *
     * Allows users to modify map elements such as start point, end point, walls, doors, etc.
     */
    void editMap();

    /**
     * @brief Edits the current campaign interactively.
     *
     * Allows users to modify maps within the campaign.
     */
    void editCampaign();

    /**
     * @brief Edits a specific map within the current campaign.
     * @param mapIndex Index of the map within the campaign to edit.
     */
    void editMapInCampaign(int mapIndex);

    /**
     * @brief Adds a new map to the current campaign.
     */
    void addNewMapToCampaign();

    /**
     * @brief Parses user input to extract coordinates and item.
     *
     * @param input Input string from the user.
     * @param x Output parameter for x-coordinate.
     * @param y Output parameter for y-coordinate.
     * @param item Output parameter for map item.
     * @return True if parsing is successful, false otherwise.
     */
    bool parseInput(const std::string& input, int& x, int& y, char& item);

    /**
     * @brief Saves the current map to a file based on user input.
     */
    void saveMapToFile();

    /**
     * @brief Saves the current campaign to a file based on user input.
     */
    void saveCampaignToFile();

    /**
     * @brief Loads a map from a file based on user input.
     */
    void loadMapFromFile();

    /**
     * @brief Loads a campaign from a file based on user input.
     */
    void loadCampaignFromFile(string pregen="");

    /**
     * @brief Clears the current map.
     *
     * Deallocates memory for the current map and resets the map pointer to nullptr.
     */
    void clearMap();

    /**
     * @brief Clears the current campaign.
     *
     * Deallocates memory for the current campaign and resets the campaign pointer to nullptr.
     */
    void clearCampaign();
};

#endif //COMP345A1_MAPEDITOR_H