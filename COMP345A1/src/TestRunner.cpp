//! @file
//! @brief Driver file to create and execute the test suite


#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//! main() function. Entry point of the program
//! It does the following:
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases.
int main()
{
    //Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    //Adds the test to the list of tests to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr));

    // Run the tests.
    bool wasSuccessful = runner.run();

    // Return error code 1 if one of the test failed.
    return wasSuccessful ? 0 : 1;

}

