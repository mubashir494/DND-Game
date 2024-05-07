#include "GameLevelMapBuilder.h"
#include <fstream>
#include <iostream>

GameLevelMapBuilder::GameLevelMapBuilder() : map(nullptr) {}

GameLevelMapBuilder::~GameLevelMapBuilder() {
    delete map;
}

void GameLevelMapBuilder::reset() {
    delete map;
    map = nullptr;
}

void GameLevelMapBuilder::loadMap(const std::string& filePath) {
    reset();
    this->map = MapBuilder::loadMapFromFile(filePath);
}

void GameLevelMapBuilder::adaptToLevel(int level) {
    for (int x = 0; x < map->getWidth(); ++x) {
        for (int y = 0; y < map->getHeight(); ++y) {
            Cell* cell = map->getCell(x, y);
            if (cell && cell->isCharacter()) {
                Character* character = cell->getCharacter();
                character->adjustLevel(level);
            }
        }
    }
}

Map* GameLevelMapBuilder::getMap() const {
    return map;
}
