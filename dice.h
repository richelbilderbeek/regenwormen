#ifndef DICE_H
#define DICE_H

#include <random>
#include <vector>
#include "die.h"

/// A collection of one or more dice
using dice = std::vector<die>;

/// Create a number of random dice
dice create_n_random_dice(const int n, std::mt19937& rng_engine);

/// Get all the permutations for picking each of the die symbols
std::vector<dice> get_all_permutations();

/// The number of dice used in the game
constexpr int get_n_dice() noexcept { return 8; }

/// Determine if there is a die with the desired symbol amongst the dice
bool has_die_with_symbol(const dice& d, const die symbol);

/// Test the dice class
void test_dice();

#endif // DICE_H
