//
// Created by hp on 18/03/2024.
//

#ifndef COMP345A1_TANKBUILDER_H
#define COMP345A1_TANKBUILDER_H


#include "FighterBuilder.h"

class TankBuilder : public FighterBuilder{
public:
    TankBuilder(void) {}
    virtual ~TankBuilder(void){}

    void setAbilityScores() override;

};


#endif //COMP345A1_TANKBUILDER_H
