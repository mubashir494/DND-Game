//
// Created by Roger Sioufi on 2024-02-24.
//

#include "TestItems.h"

//Register the test suite with CppUnit.
CPPUNIT_TEST_SUITE_REGISTRATION(TestItems);

void TestItems::testAddItem() {
    ItemContainer container;
    Item* helmet = new Helmet("Test Helmet", Enchantment{1, EnhancementType::ArmorClass});
    container.addItem(helmet);

    // Assuming ItemContainer has a method to get the count of items
    CPPUNIT_ASSERT(container.getItemCount() == 1);

    Item* armor = new Armor("Test Armor", Enchantment{2, EnhancementType::ArmorClass});
    container.addItem(armor);
    CPPUNIT_ASSERT(container.getItemCount() == 2);

}

void TestItems::testGetItem() {
    ItemContainer container;
    Item* helmet = new Helmet("Test Helmet", Enchantment{1, EnhancementType::ArmorClass});
    container.addItem(helmet);

    // Assuming ItemContainer's getItem returns a pointer to the item
    Item* retrievedItem = container.getItem(0);
    CPPUNIT_ASSERT(retrievedItem == helmet); // Check if the returned item is the same as added

}

void TestItems::testMapEditorBuilder() {
    MapEditorBuilder editorBuilder;
    std::string testFilePath = "../src/map_example.txt"; // Ensure this points to a valid test map file

    // Test loadMap
    editorBuilder.loadMap(testFilePath);
    Map* map = editorBuilder.getMap();
    CPPUNIT_ASSERT(map != nullptr); // Assert that map is loaded

    // Test reset
    editorBuilder.reset();
    CPPUNIT_ASSERT(editorBuilder.getMap() == nullptr); // Assert that map is reset properly
}

void TestItems::testGameLevelMapBuilder() {
    GameLevelMapBuilder levelBuilder;
    std::string testFilePath = "../src/map_example.txt"; // Ensure this points to a valid test level map file

    // Test loadMap
    levelBuilder.loadMap(testFilePath);
    Map* levelMap = levelBuilder.getMap();
    CPPUNIT_ASSERT(levelMap != nullptr); // Assert that level map is loaded

    // Test adaptToLevel - This requires a valid map with characters to adjust levels
    // For simplicity, assume characters' levels are adjusted by the method
    // You may need a more detailed test map and verify character levels before and after
    int testLevel = 5;
    levelBuilder.adaptToLevel(testLevel);
    // Assertions to check if characters' levels are adapted might go here

    // Test reset
    levelBuilder.reset();
    CPPUNIT_ASSERT(levelBuilder.getMap() == nullptr); // Assert that level map is reset properly
}
