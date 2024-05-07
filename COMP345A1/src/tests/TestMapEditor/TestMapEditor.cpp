#include "TestMapEditor.h"

void TestMapEditor::testMapEditor() {
    std::stringstream input_stream("1\n1\n3\n3\n1\n(0,1)S\n(2,1)E\nq\n2\ntestFileName\n3\n2\ntestFileName\n3\n3\n3\n");
    std::stringstream output_stream;

    // Redirect cin and cout
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());
    std::streambuf* old_cout = std::cout.rdbuf(output_stream.rdbuf());

    MapEditor editor;
    // Execute test
    editor.runEditor();

    // Restore cin and cout
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    std::string output = output_stream.str();
    // Check if the output contains the expected strings
    CPPUNIT_ASSERT(output.find("3x3 map created.") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Successfully Placed the Starting point") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Successfully set exit") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Map saved to file: testFileName.txt") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Map loaded from file: testFileName.txt") != std::string::npos);
}

void TestMapEditor::testCampaignEditor() {
    std::stringstream input_stream("2\n1\n5\n6\n1\n1\n(1,5)S\n(4,1)E\n(3,3)#\nq\n0\n1\n3\n4\n2\n(1,3)S\n(1,0)E\nq\n-1\n2\ntestCampaignName\n3\n2\ntestCampaignName\n3\n3\n3\n");
    std::stringstream output_stream;

    // Redirect cin and cout
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());
    std::streambuf* old_cout = std::cout.rdbuf(output_stream.rdbuf());

    MapEditor editor;
    // Execute test
    editor.runEditor();

    // Restore cin and cout
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    std::string output = output_stream.str();
    // Check if the output contains the expected strings
    CPPUNIT_ASSERT(output.find("New campaign created.") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Editing Map 1:") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Successfully set exit") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Successfully Placed the Wall") != std::string::npos);
    CPPUNIT_ASSERT(output.find("New map added to the campaign") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Editing Map 2:") != std::string::npos);
    CPPUNIT_ASSERT(output.find("All maps in the campaign are valid.") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Campaign saved to file: testCampaignName.txt") != std::string::npos);
    CPPUNIT_ASSERT(output.find("Campaign loaded from file: testCampaignName.txt") != std::string::npos);

}

CPPUNIT_TEST_SUITE_REGISTRATION(TestMapEditor);
