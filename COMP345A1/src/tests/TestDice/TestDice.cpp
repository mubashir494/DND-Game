#include "TestDice.h"
#include <cppunit/ui/text/TestRunner.h>

//Register the test suite with CppUnit.
CPPUNIT_TEST_SUITE_REGISTRATION(TestDice);

/**
 * @brief Test case for valid input to the roll method.
 */
void TestDice::testRollValidInput() {
    Dice dice;
    CPPUNIT_ASSERT_NO_THROW(dice.roll("2d6+3"));
    CPPUNIT_ASSERT_NO_THROW(dice.roll("1d20-1"));
    CPPUNIT_ASSERT_NO_THROW(dice.roll("3d10"));
}

/**
 * @brief Test case for invalid input to the roll method.
 */
void TestDice::testRollInvalidInput() {
    Dice dice;

    // Test for empty input
    try {
        dice.roll("");
        CPPUNIT_FAIL("Expected exception for empty input.");
    } catch (const std::invalid_argument& e) {
        CPPUNIT_ASSERT_EQUAL(std::string("Input string is empty."), std::string(e.what()));
    }

    // Test for invalid format
    try {
        dice.roll("2d3x");
        CPPUNIT_FAIL("Expected exception for invalid input format.");
    } catch (const std::invalid_argument& e) {
        CPPUNIT_ASSERT_EQUAL(std::string("Invalid input format. Expected format: xdy[+/-z], where x is a positive integer, y is an integer in [4, 6, 8, 10, 12, 20, 100], and z is an integer."), std::string(e.what()));
    }

    // Test for number of dice must be a positive integer
    try {
        dice.roll("0d6");
        CPPUNIT_FAIL("Expected exception for number of dice not being a positive integer.");
    } catch (const std::invalid_argument& e) {
        CPPUNIT_ASSERT_EQUAL(std::string("Number of dice must be a positive integer."), std::string(e.what()));
    }

    // Test for invalid dice type
    try {
        dice.roll("1d5");
        CPPUNIT_FAIL("Expected exception for invalid dice type.");
    } catch (const std::invalid_argument& e) {
        CPPUNIT_ASSERT_EQUAL(std::string("Invalid dice type. Allowed types: d4, d6, d8, d10, d12, d20, or d100."), std::string(e.what()));
    }
}
