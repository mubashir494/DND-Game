//
// Created by hp on 18/03/2024.
//

#ifndef COMP345A1_BULLYBUILDER_H
#define COMP345A1_BULLYBUILDER_H

#include "./FighterBuilder.h"

class BullyBuilder : public FighterBuilder {
public:
    BullyBuilder(void) {}
    virtual ~BullyBuilder(void){}

    void setAbilityScores() override;
};


#endif //COMP345A1_BULLYBUILDER_H
