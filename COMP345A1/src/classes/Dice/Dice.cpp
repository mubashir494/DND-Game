#include "Dice.h"

using namespace std;

// Constructor initializes the random number generator and compiles the regex pattern
Dice::Dice() : generator(random_device{}()), inputPattern(R"((\d+)d(\d+)([+-]\d+)?)") {
}

// Helper function to check if the input string matches the expected format
bool Dice::isValidInput(const string& input) const {
    return regex_match(input, inputPattern);
}

// Helper function to check if the given number of sides is a valid dice type
bool Dice::isValidDiceType(int numSides) const {
    // Define the set of valid dice types
    static const unordered_set<int> validDiceTypes = {4, 6, 8, 10, 12, 20, 100};
    // Check if the given number of sides is in the set of valid dice types
    return validDiceTypes.find(numSides) != validDiceTypes.end();
}

// Method to roll the dice based on the input string
int Dice::roll(const string& input) {
    // Check if the input string is empty
    if (input.empty()) {
        throw invalid_argument("Input string is empty.");
    }

    // Validate the input format
    if (!isValidInput(input)) {
        throw invalid_argument("Invalid input format. Expected format: xdy[+/-z], where x is a positive integer, y is an integer in [4, 6, 8, 10, 12, 20, 100], and z is an integer.");
    }

    // Extract the components from the input string using regular expressions
    smatch match;
    regex_search(input, match, inputPattern);
    int numDice = stoi(match[1]);
    int numSides = stoi(match[2]);
    int modifier = match[3].matched ? stoi(match[3]) : 0;

    // Check if the number of dice is positive
    if (numDice <= 0) {
        throw invalid_argument("Number of dice must be a positive integer.");
    }

    // Check if the dice type is valid
    if (!isValidDiceType(numSides)) {
        throw invalid_argument("Invalid dice type. Allowed types: d4, d6, d8, d10, d12, d20, or d100.");
    }

    // Roll the dice and calculate the total
    int total = 0;
    uniform_int_distribution<int> distribution(1, numSides);
    for (int i = 0; i < numDice; ++i) {
        total += distribution(generator);
    }

    // Apply the modifier
    total += modifier;

    notify("Dice rolled: " + std::to_string(max(1, total)));

    // Ensure the total is at least 1
    return max(1, total);
}

void Dice::attach(IObserver* observer) {
observers.push_back(observer);
}

void Dice::detach(IObserver* observer) {
observers.remove(observer);
}

void Dice::notify(const std::string& message) {
    if (loggingEnabled){
        for(auto observer : observers) {
            observer->update(message);
        }
    }
}
