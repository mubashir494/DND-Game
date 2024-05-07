cmake_minimum_required(VERSION 3.20)
project(COMP345A1)

set(CMAKE_CXX_STANDARD 20)


add_executable(COMP345A1 src/main.cpp
        src/classes/Character/Character.cpp
        src/classes/Character/Character.h
        src/classes/Fighter/Fighter.cpp
        src/classes/Item/Item.cpp
        src/classes/Helmet/Helmet.cpp

        src/classes/Armor/Armor.cpp
        src/classes/Shield/Shield.cpp
        src/classes/Ring/Ring.cpp
        src/classes/Belt/Belt.cpp
        src/classes/Boots/Boots.cpp
        src/classes/Weapon/Weapon.cpp
        src/classes/Cell/Cell.cpp
        src/classes/Map/Map.cpp
        src/classes/Dice/Dice.cpp
        src/classes/ObserverPattern/Subject.h
        src/classes/ObserverPattern/Observer.h
        src/classes/ObserverPattern/Subject.cpp
        src/classes/ObserverPattern/Observer.cpp
        src/classes/ObserverPattern/CharacterObserver.h
        src/classes/ObserverPattern/CharacterObserver.cpp
        src/classes/CellContent/CellContent.cpp
        src/classes/CellContent/CellContent.h
        src/classes/ObserverPattern/MapObserver.cpp
        src/classes/ObserverPattern/MapObserver.h
        src/classes/ObserverPattern/MapObserver.h
        src/classes/MapEditor/MapEditor.cpp
        src/classes/Campaign/Campaign.cpp
        src/classes/MapBuilders/MapBuilder.h
        src/classes/MapBuilders/MapEditorBuilder.cpp
        src/classes/MapBuilders/MapEditorBuilder.h
        src/classes/MapBuilders/GameLevelMapBuilder.cpp
        src/classes/MapBuilders/GameLevelMapBuilder.h
        src/classes/Builder/BullyBuilder.cpp
        src/classes/Builder/BullyBuilder.h
        src/classes/Builder/BullyBuilder.h
        src/classes/Builder/FighterBuilder.h
        src/classes/Builder/NimbleBuilder.cpp
        src/classes/Builder/NimbleBuilder.h
        src/classes/Builder/TankBuilder.cpp
        src/classes/Builder/TankBuilder.h
        src/classes/Builder/TankBuilder.h
        src/classes/CharacterStrategy/CharacterStrategy.h
        src/classes/CharacterStrategy/CharacterStrategy.cpp
        src/classes/GameLogger/GameLogger.h
        src/classes/CharacterEditor/CharacterEditor.cpp
        src/classes/CharacterEditor/CharacterEditor.h
        src/classes/ItemContainerEditor/ItemContainerEditor.cpp
        src/classes/ItemContainerEditor/ItemContainerEditor.h
        src/classes/Game/Game.cpp
        src/classes/Game/Game.h
        src/classes/Map/Map.h
        src/classes/ItemContainer/ItemContainer.h
        src/classes/ItemContainer/ItemContainer.cpp


)


# Test suite
enable_testing()
add_executable(UnitTests src/TestRunner.cpp
        src/classes/Character/Character.cpp
        src/classes/Fighter/Fighter.cpp
        src/tests/TestFighter/TestFighter.cpp
        src/classes/Dice/Dice.cpp
        src/classes/Item/Item.cpp
        src/classes/Helmet/Helmet.cpp
        src/classes/ItemContainer/ItemContainer.cpp
        src/classes/CellContent/CellContent.cpp
        src/classes/Armor/Armor.cpp
        src/classes/ObserverPattern/Subject.cpp
        src/classes/ObserverPattern/Observer.cpp
        src/classes/Shield/Shield.cpp
        src/classes/Ring/Ring.cpp
        src/classes/Belt/Belt.cpp
        src/classes/Boots/Boots.cpp
        src/classes/Cell/Cell.cpp
        src/classes/Map/Map.cpp
        src/classes/Fighter/Fighter.cpp
        src/classes/Weapon/Weapon.cpp
        src/classes/ObserverPattern/Subject.cpp
        src/tests/TestDice/TestDice.cpp
        src/tests/TestItems/TestItems.cpp
        src/tests/TestMap/TestMap.cpp
        src/classes/Campaign/Campaign.cpp
        src/classes/MapEditor/MapEditor.cpp
        src/tests/TestMapEditor/TestMapEditor.cpp
        src/tests/TestMapEditor/TestMapEditor.h
        src/classes/MapBuilders/MapBuilder.h
        src/classes/MapBuilders/MapEditorBuilder.cpp
        src/classes/MapBuilders/MapEditorBuilder.h
        src/classes/MapBuilders/GameLevelMapBuilder.cpp
        src/classes/MapBuilders/GameLevelMapBuilder.h
)


if(APPLE) # CppUnit configuration for Mac users
    # Include directories for CppUnit headers
    target_include_directories(UnitTests PRIVATE "/usr/local/opt/cppunit/include")

    #Specify the output directory for the UnitTests executable
    set_target_properties(UnitTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    # Link directories for CppUnit library
    target_link_directories(UnitTests PRIVATE "/usr/local/opt/cppunit/lib")

    # Link against the CppUnit library
    target_link_libraries(UnitTests debug cppunit optimized cppunit)

elseif(WIN32) # CppUnit configuration for Windows users
    # Include directories for CppUnit headers
    target_include_directories(UnitTests PRIVATE "./CppUnit/include")

    # Link directories for CppUnit library
    target_link_directories(UnitTests PRIVATE "./CppUnit/lib")

    # Link against the CppUnit library
    target_link_libraries(UnitTests debug "cppunitd.lib" optimized "cppunit.lib")
endif()
