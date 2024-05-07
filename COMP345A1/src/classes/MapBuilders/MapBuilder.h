/**
 * @file MapBuilder.h
 * @brief Abstract base class for map builders in a d20 game.
 *
 * Game Rules: This builder pattern is used to construct maps for different scenarios within the game,
 * allowing for the dynamic creation and adaptation of maps for gameplay and editing.
 *
 * Design: This class follows the Builder pattern to abstract the construction of map objects. It allows
 * for different representations of maps to be constructed and manipulated. The class provides a static method
 * for loading maps from files directly, facilitating reuse across different builder implementations.
 *
 * Libraries:
 * - `<string>`: Used for handling strings, essential for file paths and text manipulation.
 * - `<fstream>`: Utilized for file input/output operations, crucial for reading map data from files.
 * - `<iostream>`: Used for console input and output, including error messages, enhancing user interaction and debugging.
 *
 */
#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "../Map/Map.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector> // For storing lines from the file

class MapBuilder {
public:
    /**
     * @brief Virtual destructor for the MapBuilder class.
     */
    virtual ~MapBuilder() {}

    /**
     * @brief Resets the builder to its initial state, preparing it for creating a new map.
     */
    virtual void reset() = 0;

    /**
     * @brief Adapts the map to a specific level, adjusting elements as necessary.
     *
     * This method is intended for concrete implementations that need to modify map contents
     * based on gameplay level, such as adjusting opponent strength.
     *
     * @param level The gameplay level to adapt the map's contents to.
     */
    virtual void adaptToLevel(int level) = 0;

    /**
     * @brief Retrieves the current map object being constructed.
     *
     * @return Map* A pointer to the constructed Map object, if available.
     */
    virtual Map* getMap() const = 0;

    /**
     * @brief Loads a map from a specified file path. This method is to be implemented by concrete builders.
     *
     * @param filePath The path to the file containing the map data.
     */
    virtual void loadMap(const std::string& filePath) = 0;

    /**
     * @brief Static method to load a map from a file, creating a Map object with dimensions and contents based on the file.
     *
     * This utility function reads a map file, dynamically determines its dimensions, and populates a new Map instance accordingly.
     * It handles reading the file, creating the map, and ensuring the map's contents match the file.
     *
     * @param filePath The path to the file containing the map data.
     * @return Map* A new Map object populated with the contents from the file, or nullptr if the file could not be opened.
     */
    static Map* loadMapFromFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open map file: " << filePath << std::endl;
            return nullptr;
        }

        int width = 0, height = 0;
        std::string line;

        std::vector<std::string> lines;
        while (std::getline(file, line)) {
            lines.push_back(line);
            height++;
            width = line.length() > width ? line.length() : width; // Ensure width is max line length
        }
        file.close();

        // Now that we have dimensions, create the map
        Map* map = new Map(width, height);

        // Populate the map
        for (int y = 0; y < height; ++y) {
            for (size_t x = 0; x < lines[y].length(); ++x) {
                char item = lines[height - y - 1][x];
                map->Place(x, y, item);
            }
        }

        return map;
    }

};

#endif // MAPBUILDER_H