#ifndef DICE_H
#define DICE_H

#include <iosfwd>
#include <random>
#include <vector>
#include "die.h"

/// A collection of one or more dice
using dice = std::vector<die>;

/// Create a number of random dice
dice create_n_random_dice(const int n, std::mt19937& rng_engine);

/// Get all the 1956 permutations for picking each of the six die symbols, for any number of (non-empty) die symbol set size
/// For example:
///   {1,2,3,4,5,W}
///   {1,2,3,4,W,5}
///   ...
///   {1, 2},
///   {1, W},
///   ...
///   {1}
///   {W}
std::vector<dice> get_all_permutations();


/// Get all the permutations for picking each of die symbols
std::vector<dice> get_all_permutations_for_subset(dice ds);

/// The number of dice used in the game
constexpr int get_n_dice() noexcept { return 8; }

/// Are there a worm in this collection of die symbols?
bool has_worm(const dice& ds) noexcept;

/// Determine if there is a die with the desired symbol amongst the dice
bool has_die_with_symbol(const dice& d, const die symbol);

/// Test the dice class
void test_dice();

std::string to_str(const dice& ds);

std::ostream& operator<<(std::ostream& os, const dice& ds);

#endif // DICE_H
