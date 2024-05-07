//
// Created by hp on 07/03/2024.
//

#ifndef COMP345A1_MAPOBSERVER_H
#define COMP345A1_MAPOBSERVER_H

#include "Observer.h"
#include "../Map/Map.h"

class MapObserver : public Observer{
public:

    //! default constructor of the MapObserver class
    MapObserver();
    /**
    * @brief Create an observer to a Map
    *
    * @param map The Map to be observed.
    */
     MapObserver(Map* map);

    //! Destructor of the MapObserver class
    ~MapObserver();

    //! method that updates the state of the MapObserver
    void update();

private:
    Map* _subject;

};


#endif //COMP345A1_MAPOBSERVER_H
