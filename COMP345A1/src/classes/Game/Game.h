//
// Created by hp on 01/04/2024.
//

#ifndef COMP345A1_GAME_H
#define COMP345A1_GAME_H

#include "../Campaign/Campaign.h"
#include "../MapEditor/MapEditor.h"


class Game {
public:
    Game() {campaign = nullptr;};
    void play();
    vector<Character*> initiativeRoll(vector<Character*> chars);
private:
    Campaign* loadPregeneratedCampaign();
    bool getCampaign();
    Campaign *campaign;
};


#endif //COMP345A1_GAME_H
