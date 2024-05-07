//! @file
//! @brief File containing the implmentation of the Test Methods
//!

#include "TestFighter.h"

//Register the test suite with CppUnit.
CPPUNIT_TEST_SUITE_REGISTRATION(TestFighter);

//! setUp() method that is executed before all the test cases that the test class includes
void TestFighter::setUp(void) {
    fighterObject = new Fighter("Fighter", 5);
}

//! tearDown() method that is executed after all the test cases that the test class includes
void TestFighter::tearDown(void) {
    delete fighterObject;
}

//! test method to test the calculateHitpoints() method of the Fighter class
//! Test Case: hitpoints == 10 + level + Con modifier
void TestFighter::testCalculateHitpoints() {
    int constitutionModifier = fighterObject->getModifiers()["Constitution"];

    CPPUNIT_ASSERT(fighterObject->getHitpoints() == 10 + fighterObject->getLevel() * constitutionModifier );
}

//! test method to test the calculateAttackBonus() method of the Fighter class
//! Test Case: attackBonus == level + Str modifier
void TestFighter::testCalculateAttackBonus() {

    CPPUNIT_ASSERT(fighterObject->getLevel() + fighterObject->getModifiers()["Strength"] == fighterObject->getAttackBonus());
}

void TestFighter::testAdjustLevel(void) {
    int initialLevel = fighterObject->getLevel();

    fighterObject->adjustLevel(20);

    int currentLevel = fighterObject->getLevel();

    CPPUNIT_ASSERT(currentLevel != initialLevel);
}

void TestFighter::testAdjustLevelAttackBonusChange(void) {
    int initialAttackBonus = fighterObject->getAttackBonus();

    fighterObject->adjustLevel(20);

    int currentAttackBonus = fighterObject->getAttackBonus();
    CPPUNIT_ASSERT(currentAttackBonus != initialAttackBonus);
}