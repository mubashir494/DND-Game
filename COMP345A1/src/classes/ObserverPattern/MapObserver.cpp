//
// Created by hp on 07/03/2024.
//

#include "MapObserver.h"

MapObserver::MapObserver() {

}

MapObserver::MapObserver(Map *map) {
    _subject = map;
    _subject->Attach(this);

}

MapObserver::~MapObserver() {
    _subject->Detach(this);
}

void MapObserver::update() {
    _subject->printMap();
}


