#include "MapEditorBuilder.h"
#include <fstream>
#include <iostream>

MapEditorBuilder::MapEditorBuilder() : map(nullptr) {}

MapEditorBuilder::~MapEditorBuilder() {
    delete map;
}

void MapEditorBuilder::reset() {
    delete map;
    map = nullptr;
}

void MapEditorBuilder::loadMap(const std::string& filePath) {
    reset();
    this->map = MapBuilder::loadMapFromFile(filePath);
}

void MapEditorBuilder::adaptToLevel(int level) {
    // Not applicable for MapEditorBuilder
}

Map* MapEditorBuilder::getMap() const {
    return map;
}
