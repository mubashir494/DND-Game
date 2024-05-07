//
// Created by hp on 18/03/2024.
//

#ifndef COMP345A1_NIMBLEBUILDER_H
#define COMP345A1_NIMBLEBUILDER_H


#include "FighterBuilder.h"

class NimbleBuilder : public FighterBuilder{
public:
    NimbleBuilder(void) {}
    virtual ~NimbleBuilder(void){}

    void setAbilityScores() override;

};


#endif //COMP345A1_NIMBLEBUILDER_H
