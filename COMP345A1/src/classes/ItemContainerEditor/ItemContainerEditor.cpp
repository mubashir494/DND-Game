//
// Created by hp on 30/03/2024.
//
#include "ItemContainerEditor.h"
#include "../Armor/Armor.h"
#include "../Boots/Boots.h"
#include "../Helmet/Helmet.h"
#include "../Ring/Ring.h"
#include "../Shield/Shield.h"
#include "../Weapon/Weapon.h"
#include "../Belt/Belt.h"

ItemContainer* ItemContainerEditor::run(ItemContainer *container) {
    int input;
    while(true){
        cout << "What Type of Item You want to Add :" << endl;
        cout << "\nChoose an option:" << endl;
        cout << "1: Armor" << endl;
        cout << "2: Belt" << endl;
        cout << "3: Boots" << endl;
        cout << "4: Helmet" << endl;
        cout << "5: Ring" << endl;
        cout << "6: Shield" << endl;
        cout << "7: Weapon" << endl;
        cout << "8 : Quit" << endl;
        cout << "Enter option: ";
        cin >> input ;
        switch(input){
            case 1 : {
                string name;
                cout << "\nGive the item an identifier :";
                cin >>name;
                Item *item = new Armor(name);
                abilityMenu(item);
                container->addItem(item);
                break;
            }
            case 2 : {
                string name;
                cout << "\nGive the item an identifier :";
                cin >> name;
                Item *item = new Belt(name);
                abilityMenu(item);
                container->addItem(item);
                break;
            }
            case 3 : {
                string name;
                cout << "\nGive the item an identifier :";
                cin >> name;
                Item *item = new Boots(name);
                abilityMenu(item);
                container->addItem(item);
                break;
            }

            case 4 :{
                string name;
                cout << "\nGive the item an identifier :";
                cin >> name;
                Item *item = new Helmet(name);
                abilityMenu(item);
                container->addItem(item);
                break;
            }

            case 5 : {
                string name;
                cout << "\nGive the item an identifier :";
                cin >> name;
                Item *item = new Ring(name);
                abilityMenu(item);
                container->addItem(item);
                break;
            }
            case 6 : {
                string name;
                cout << "\nGive the item an identifier :";
                cin >> name;
                Item *item = new Shield(name);
                abilityMenu(item);
                container->addItem(item);
                break;
            }
            case 7 : {
                weaponSelector(container);
                break;
            }
            case 8 : {
                return container;
            }
        }
    }
}


void ItemContainerEditor::weaponSelector(ItemContainer* container) {
    while(true) {
        int option;
        cout << "\nWhat Type of Weapons" << endl;
        cout << "Enter an Option: " << endl;
        cout << "1: Sword" << endl;
        cout << "2: Bow" << endl;
        cout << "Enter Option : ";
        cin >> option;
        Weapon *weapon = nullptr;
        switch (option){
            case 1 : {
                string name;
                cout << "\nGive the item an identifier : ";
                cin >> name;
                weapon = new Weapon(name,Weapon::WeaponType::SWORD);
                abilityMenu(weapon);
                container->addItem(weapon);
                break;

            }
            case 2: {
                string name;
                cout << "\nGive the item an identifier : ";
                cin >> name;
                weapon = new Weapon(name,Weapon::WeaponType::BOW);
                abilityMenu(weapon);
                container->addItem(weapon);
                break;
            }
        }
        if(weapon != nullptr){
            return;
        }
    }
}

void ItemContainerEditor::abilityMenu(Item* item) {
    int input;

    while(true){
        cout << "What Modifiers Do you want to Edit (Value must be less than 5)" << endl;
        cout << "\nChoose an option:" << endl;
        cout << "1: Strength" << endl;
        cout << "2: Dexterity" << endl;
        cout << "3: Constitution" << endl;
        cout << "4: Intelligence" << endl;
        cout << "5: Wisdom" << endl;
        cout << "6: Intelligence" << endl;
        cout << "7: Attack Bonus" << endl;
        cout << "8 :Damage Bonus" << endl;
        cout << "9 :Hit Points" << endl;
        cout << "10 :Armor" << endl;
        cout << "11 :Quit" << endl;
        cin >> input;

        switch (input) {
            case 1 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setAbilityScores("Strength",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 2 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setAbilityScores("Dexterity",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 3 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setAbilityScores("Wisdom",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 4 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setAbilityScores("Intelligence",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;

            }
            case 5 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setAbilityScores("Wisdom",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 6 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setAbilityScores("Intelligence",score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 7 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setAttackBonus(score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 8 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setDamageBonus(score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 9 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setHitpoints(score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 10 : {
                int score;
                cout << "Set a score: "<< endl;
                cin >> score;
                if(score > 0 && score <= 5){
                    item->setArmorClass(score);
                }
                else {
                    cout << "Value is less then equal to 0 or greater then 5 "<<endl;
                }
                break;
            }
            case 11 : {
                return;
            }
        }
    }
}


