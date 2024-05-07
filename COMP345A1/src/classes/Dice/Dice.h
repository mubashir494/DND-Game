#ifndef COMP345A1_DICE_H
#define COMP345A1_DICE_H

#include <string>
#include <stdexcept>
#include <random>
#include <unordered_set>
#include <regex>
#include <list>

#include "../GameLogger/GameLogger.h"

/**
 * @brief Represents a class for rolling dice in a tabletop role-playing game (RPG) context.
 *
 * This class provides support for rolling dice commonly used in RPGs, specifically d4, d6, d8, d10, d12, d20, and d100.
 * It allows rolling any number of dice of one kind at once using the format "xdy[+z]", where x is the number of dice
 * to roll, y is the number of sides on each die (allowed values: 4, 6, 8, 10, 12, 20, 100), and z is an optional modifier
 * to add after all the dice results have been totaled.
 *
 * The design of this class is based on encapsulating the functionality of rolling dice, parsing the input string,
 * and handling errors for invalid input formats. It uses the Mersenne Twister random number generator from the
 * C++ standard library for generating random numbers to simulate dice rolls.
 *
 * The choice of using the Mersenne Twister random number generator was made due to its good statistical properties
 * and high-quality random number generation, which is important for simulating fair and unbiased dice rolls in
 * role-playing games.
 *
 * @par Game Rules:
 * The class assumes standard RPG dice rules, where each die has a specific number of sides (4, 6, 8, 10, 12, 20, or 100).
 * For example, a d20 refers to a 20-sided die, and rolling it involves generating a random number between 1 and 20.
 * The class supports rolling multiple dice of the same type at once, with an optional modifier added to the total
 * after all the dice results have been summed. However, the modifier ensures that the final result is never negative,
 * even if the modifier would reduce it below zero. In such cases, the result is clamped to a minimum of 1, consistent
 * with standard d20 game rules.
 *
 * @par Libraries Used:
 * - <random>: Used for generating random numbers. The Mersenne Twister algorithm provides high-quality random number
 *             generation, suitable for simulating fair and unbiased dice rolls in role-playing games.
 * - <string>: Used for handling input strings representing dice rolls and modifiers.
 * - <stdexcept>: Used for throwing exceptions when encountering errors such as invalid input formats.
 * - <unordered_set>: Used for storing valid dice types in a set data structure for efficient lookup during validation.
 * - <regex>: Used for input string validation using regular expressions.
 */

class Dice : public IObservable {
private:
    std::mt19937 generator; /**< Mersenne Twister random number generator */
    std::regex inputPattern; /**< Regular expression pattern for input validation */

    /**
     * @brief Checks if the input string matches the expected format.
     *
     * @param input The input string to check.
     * @return true if the input string matches the expected format, false otherwise.
     */
    bool isValidInput(const std::string& input) const;

    /**
     * @brief Checks if the given number of sides is a valid dice type.
     *
     * @param numSides The number of sides on the die.
     * @return true if the number of sides is a valid dice type, false otherwise.
     */
    bool isValidDiceType(int numSides) const;

    std::list<IObserver*> observers;

public:
    /**
     * @brief Constructs a Dice object.
     *
     * Initializes the random number generator for rolling the dice.
     */
    Dice();

    /**
     * @brief Rolls the dice based on the input string.
     *
     * The input string represents the dice roll in the format "xdy[+z]". Here, x is the number of dice,
     * y is the number of sides on each die (allowed values: 4, 6, 8, 10, 12, 20, 100), and z is an optional modifier
     * (positive or negative).
     *
     * @param input The input string representing the dice roll.
     * @return The result of the dice roll.
     * @throw std::invalid_argument if the input format is invalid or if the number of dice is not positive
     *        or if the dice type is invalid.
     */
    int roll(const std::string& input);

    void attach(IObserver* observer) override;

    void detach(IObserver* observer) override;

    void notify(const std::string& message) override;
};
#endif //COMP345A1_DICE_H
