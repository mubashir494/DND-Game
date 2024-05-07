#include <cppunit/extensions/HelperMacros.h>
#include "../../classes/ItemContainer/ItemContainer.h"
#include "../../classes/Item/Item.h"
#include "../../classes/Helmet/Helmet.h"
#include "../../classes/Armor/Armor.h"
#include "../../classes/MapBuilders/GameLevelMapBuilder.h"
#include "../../classes/MapBuilders/MapEditorBuilder.h"
class TestItems : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestItems);
        CPPUNIT_TEST(testAddItem);
        CPPUNIT_TEST(testGetItem);
        CPPUNIT_TEST(testMapEditorBuilder);
        CPPUNIT_TEST(testGameLevelMapBuilder);
    CPPUNIT_TEST_SUITE_END();

public:
    void testAddItem();
    void testGetItem();
    void testMapEditorBuilder();
    void testGameLevelMapBuilder();
};
