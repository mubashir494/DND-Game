#ifndef COMP345A1_TESTDICE_H
#define COMP345A1_TESTDICE_H

#include <cppunit/extensions/HelperMacros.h>
#include "../../classes/Dice/Dice.h"

/**
 * @brief A class containing unit tests for the Dice class.
 */
class TestDice : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestDice);
        CPPUNIT_TEST(testRollValidInput);
        CPPUNIT_TEST(testRollInvalidInput);
    CPPUNIT_TEST_SUITE_END();

public:
    /**
     * @brief Test case for valid input to the roll method.
     */
    void testRollValidInput();

    /**
     * @brief Test case for invalid input to the roll method.
     */
    void testRollInvalidInput();
};

#endif //COMP345A1_TESTDICE_H
