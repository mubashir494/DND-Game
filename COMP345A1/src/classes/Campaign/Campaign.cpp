
#include "Campaign.h"

Campaign::Campaign(int initialWidth, int initialHeight) : numMaps(1) {
    maps = new Map*[numMaps];
    maps[0] = new Map(initialWidth, initialHeight); // Create the first map
}

Campaign::~Campaign() {
    for (int i = 0; i < numMaps; ++i) {
        delete maps[i];
    }
    delete[] maps;
}

void Campaign::addMap(Map* map) {
    // Dynamically allocate a larger array
    Map** newMaps = new Map*[numMaps + 1];
    // Copy existing maps to the new array
    for (int i = 0; i < numMaps; ++i) {
        newMaps[i] = maps[i];
    }
    // Add the new map
    newMaps[numMaps++] = map;
    // Delete the old array and update the pointers
    delete[] maps;
    maps = newMaps;

    if (numMaps > 1) { // If there's more than one map, link them
        maps[numMaps - 2]->setNextMap(maps[numMaps - 1]); // Set the previous map's nextMap to newMap
        maps[numMaps - 1]->setPrevMap(maps[numMaps - 2]); // Set newMap's prevMap to the previous map
    }
}

void Campaign::printCampaign() {
    std::cout << "\nCampaign:" << std::endl;
    cout << "\tNumber of maps = " << numMaps << endl;
    std::cout << "------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numMaps; ++i) {
        std::cout << "\tMap " << i + 1 << ":" << std::endl;
        if (maps[i]) {
            maps[i]->printMap();
        } else {
            std::cout << "Map is null." << std::endl;
        }
    }
}

bool Campaign::isValid() {
    for (int i = 0; i < numMaps; ++i) {
        if (!maps[i]->isValid()) {
            std::cout << "\nMap " << i + 1 << " is not valid." << std::endl;
            return false;
        }
    }
    std::cout << "\nAll maps in the campaign are valid." << std::endl;
    return true;
}

int Campaign::getNumMaps() {
    return numMaps;
}

Map* Campaign::getMap(int index) {
    if (index >= 0 && index < numMaps) {
        return maps[index];
    }
    return nullptr;
}

// Serialization method for Campaign
std::ostream& operator<<(std::ostream& os, const Campaign& campaign) {
    os << campaign.numMaps << " "; // Serialize number of maps
    // Serialize each map in the campaign
    for (int i = 0; i < campaign.numMaps; ++i) {
        os << *(campaign.maps[i]) ; // Serialize map
    }
    return os;
}

// Deserialization method for Campaign
std::istream& operator>>(std::istream& is, Campaign& campaign) {
    is >> campaign.numMaps; // Deserialize number of maps
    // Allocate memory for maps
    campaign.maps = new Map*[campaign.numMaps];
    // Deserialize each map in the campaign
    for (int i = 0; i < campaign.numMaps; ++i) {
        campaign.maps[i] = new Map(0, 0); // Initialize map with default dimensions
        is >> *(campaign.maps[i]); // Deserialize map
    }
    return is;
}