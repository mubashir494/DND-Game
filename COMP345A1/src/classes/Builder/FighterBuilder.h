//
// Created by hp on 18/03/2024.
//

#ifndef COMP345A1_FIGHTERBUILDER_H
#define COMP345A1_FIGHTERBUILDER_H

#include "../Fighter/Fighter.h"


class FighterBuilder {
public:
    /**
     * Creates a Builder Class
     */
    FighterBuilder() {};

    /**
     * Destructor for Builder class
     */
    virtual ~FighterBuilder() {}

    /**
     * Creates a new Fighter
     * @param name
     * @param level
     */
    void createFighter(const string& name,int level) {fighter = new Fighter(name,level);}

    Fighter* getFighter() { return fighter;}

    /**
     * Sets Ability Score according to the Builder
     */
    virtual void setAbilityScores() = 0;

protected:
    /**
     * Stores fighter
     */
    Fighter* fighter;
};


#endif //COMP345A1_FIGHTERBUILDER_H
