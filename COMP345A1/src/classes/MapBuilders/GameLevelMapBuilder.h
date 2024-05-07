/**
 * @file GameLevelMapBuilder.h
 * @brief Concrete builder for adapting maps to specific game levels for a d20 game.
 *
 * Game Rules: This builder adapts a loaded map's content (e.g., characters, items) to the appropriate level
 * for the gameplay, ensuring challenges are scaled according to the player's progress.
 *
 * Design: Part of the Builder pattern focusing on adapting maps for gameplay. It modifies map elements based on
 * the input level, enabling dynamic difficulty adjustments and enhancing gameplay variety.
 *
 * Libraries: <string> for file paths, I/O operations for map loading.
 *
 */
#ifndef GAMELEVELMAPBUILDER_H
#define GAMELEVELMAPBUILDER_H

#include "MapBuilder.h"

class GameLevelMapBuilder : public MapBuilder {
private:
    Map* map; ///< Pointer to the map being built and adapted.
public:
    /**
     * @brief Constructs a new Game Level Map Builder object.
     */
    GameLevelMapBuilder();

    /**
     * @brief Destroys the Game Level Map Builder object, ensuring proper cleanup.
     */
    virtual ~GameLevelMapBuilder();

    /**
     * @brief Resets the builder, preparing it for a new map construction.
     */
    virtual void reset() override;

    /**
     * @brief Loads a map from a specified file path and initializes it without level adaptation.
     *
     * @param filePath The path to the map file to be loaded.
     */
    virtual void loadMap(const std::string& filePath) override;

    /**
     * @brief Adapts the currently loaded map's content to a specified level.
     *
     * This involves iterating over the map's elements and adjusting their properties
     * (e.g., character levels) to match the input level, enhancing gameplay dynamics.
     *
     * @param level The level to which the map's contents will be adapted.
     */
    virtual void adaptToLevel(int level) override;

    /**
     * @brief Retrieves the currently built and adapted map.
     *
     * @return Map* A pointer to the constructed Map object.
     */
    virtual Map* getMap() const override;
};

#endif // GAMELEVELMAPBUILDER_H
