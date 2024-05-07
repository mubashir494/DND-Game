/**
 * @file TestFighter.h
 * @brief Defines the Test suite for the Fighter class.
 *
 * Declares unit tests for the Fighter class using the CppUnit framework.
 */


#include "cppunit/extensions/HelperMacros.h"

#include "../../classes/Fighter/Fighter.h"

using namespace std;

//! Test Class for the Fighter class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite.
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestFighter : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TestFighter);
        CPPUNIT_TEST(testCalculateHitpoints);
        CPPUNIT_TEST(testCalculateAttackBonus);
        CPPUNIT_TEST(testAdjustLevel);
        CPPUNIT_TEST(testAdjustLevelAttackBonusChange);
        CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testCalculateHitpoints(void);
    void testCalculateAttackBonus(void);
    void testAdjustLevel(void);
    void testAdjustLevelAttackBonusChange(void);


private:
    Fighter *fighterObject;

};
