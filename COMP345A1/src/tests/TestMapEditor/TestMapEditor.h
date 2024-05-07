#ifndef COMP345A1_TESTMAPEDITOR_H
#define COMP345A1_TESTMAPEDITOR_H

#include <cppunit/extensions/HelperMacros.h>
#include "../../classes/MapEditor/MapEditor.h"
#include <iostream>
#include <sstream>

/**
 * @brief Represents unit tests for the MapEditor class.
 * 
 * The TestMapEditor class contains unit tests to verify the functionality of the MapEditor class.
 * It simulates user input and captures program output to validate various features of the MapEditor.
 * 
 * Game Rules:
 * - Test cases cover various scenarios of map and campaign creation, editing, saving, and loading.
 * - Assertions are used to ensure that expected behaviors are exhibited by the MapEditor.
 * 
 * Class Design:
 * - Uses CppUnit framework for defining and running unit tests.
 * - Includes mock input and output stream classes for simulating user input and capturing program output.
 * - Tests are organized into test suites, each focusing on a specific aspect of the MapEditor functionality.
 * 
 * Library Selection Rationale:
 * - CppUnit: Provides a framework for writing and executing unit tests in C++.
 * - iostream: Standard Input/Output Stream Library for handling console input/output.
 * - sstream: Used for string manipulation to simulate user input and capture program output.
 */
class TestMapEditor : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestMapEditor);
        CPPUNIT_TEST(testMapEditor);
        CPPUNIT_TEST(testCampaignEditor);
    CPPUNIT_TEST_SUITE_END();

public:
    /**
     * @brief Tests the map editor functionality.
     */
    void testMapEditor();

    /**
     * @brief Tests the campaign editor functionality.
     */
    void testCampaignEditor();
};

#endif //COMP345A1_TESTMAPEDITOR_H