/**
 * @file MapEditorBuilder.h
 * @brief Concrete builder for creating and loading maps in a map editor context for a d20 game.
 *
 * Game Rules: This builder allows the map editor to load and manipulate maps without applying game-level adaptations.
 * It is intended for map creation and testing within an editing environment, providing tools for direct manipulation
 * and inspection of map structures.
 *
 * Design: Implements the Builder pattern to construct a Map object from a file, specifically for use in editing
 * scenarios. It provides a clear separation of concerns between map editing and gameplay map adaptation,
 * ensuring that maps can be created and modified without altering their intended gameplay dynamics.
 *
 * Libraries:
 * - `<string>` for file path handling, crucial for locating and reading map files.
 * - I/O operations (`<fstream>`, `<iostream>`) for reading map files and reporting errors.
 */
#ifndef MAPEDITORBUILDER_H
#define MAPEDITORBUILDER_H

#include "MapBuilder.h"

class MapEditorBuilder : public MapBuilder {
private:
    Map* map; ///< Pointer to the map being constructed and manipulated.
public:
    /**
     * @brief Constructs a new Map Editor Builder object.
     */
    MapEditorBuilder();

    /**
     * @brief Destroys the Map Editor Builder object, ensuring proper cleanup of resources.
     */
    virtual ~MapEditorBuilder();

    /**
     * @brief Resets the builder to its initial state, ready for a new map creation or loading.
     * This function clears the current map instance, preparing for the loading or creation of a new map.
     */
    virtual void reset() override;

    /**
     * @brief Loads a map from the specified file path, creating a Map object based on its contents.
     * This function reads the map data from the provided file and constructs a map accordingly,
     * without applying any gameplay level adaptations, making it suitable for map editing purposes.
     *
     * @param filePath The path to the map file to be loaded.
     */
    virtual void loadMap(const std::string& filePath) override;

    /**
     * @brief Adapts the map to a specific level. In the context of MapEditorBuilder, this function
     * does not perform any operation, as level adaptation is not relevant for map editing.
     *
     * @param level The level parameter is ignored in this implementation.
     */
    virtual void adaptToLevel(int level) override; // No operation for editor

    /**
     * @brief Retrieves the map currently managed by the builder.
     * This function returns a pointer to the Map object that has been loaded or constructed,
     * allowing for further manipulation or inspection.
     *
     * @return Map* A pointer to the constructed or loaded Map object.
     */
    virtual Map* getMap() const override;
};

#endif // MAPEDITORBUILDER_H
