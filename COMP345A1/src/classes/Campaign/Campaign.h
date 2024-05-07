#ifndef COMP345A1_CAMPAIGN_H
#define COMP345A1_CAMPAIGN_H

#include "../Map/Map.h"
#include <iostream> // Standard Input/Output Stream Library for printing

/**
 * @brief Represents a campaign in a simple d20 game.
 * 
 * A campaign consists of multiple maps, where players navigate through.
 * The class provides functionality to manage and manipulate these maps.
 * 
 * Game Rules:
 * - A campaign consists of multiple maps linked together.
 * - Players navigate through maps to accomplish objectives.
 * - Each map must be valid, ensuring consistent gameplay experience.
 * 
 * Class Design:
 * - Campaign class manages multiple Map objects.
 * - Provides methods to add maps, print the campaign, check validity, and access individual maps.
 * - Serialization methods are provided to facilitate saving/loading campaigns.
 * 
 * Library Selection Rationale:
 * - iostream: Used for basic input/output operations, essential for printing campaign details.
 * 
 */
class Campaign {
public:
    /**
     * @brief Constructor to initialize the Campaign.
     * @param initialWidth Width of the initial map.
     * @param initialHeight Height of the initial map.
     */
    Campaign(int initialWidth, int initialHeight);

    /**
     * @brief Destructor to clean up memory allocated by maps.
     */
    ~Campaign();

    /**
     * @brief Add a map to the campaign.
     * @param map Pointer to the map to be added.
     */
    void addMap(Map* map);

    /**
     * @brief Print details of all maps in the campaign.
     */
    void printCampaign();

    /**
     * @brief Check if all maps in the campaign are valid.
     * @return True if all maps are valid, false otherwise.
     */
    bool isValid();

    /**
     * @brief Get the number of maps in the campaign.
     * @return Number of maps.
     */
    int getNumMaps();

    /**
     * @brief Get a specific map from the campaign.
     * @param index Index of the map to retrieve.
     * @return Pointer to the requested map.
     */
    Map* getMap(int index);

    /**
     * @brief Serialization method to save the campaign to an output stream.
     * @param os Output stream to save the campaign data.
     * @param campaign Reference to the Campaign object to serialize.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Campaign& campaign);

    /**
     * @brief Deserialization method to load the campaign from an input stream.
     * @param is Input stream containing the serialized campaign data.
     * @param campaign Reference to the Campaign object to deserialize into.
     * @return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream& is, Campaign& campaign);

    Map** maps;


private:
    // user Character
    Character* character;
    // Which map the user is currently on
    int currentMapIndex;
    // Regular array to store maps
    // num of maps
    int numMaps;
};

#endif //COMP345A1_CAMPAIGN_H