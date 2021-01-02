#ifndef DICE_H
#define DICE_H

#include <random>
#include <vector>
#include "die.h"

/// A collection of one or more dice
using dice = std::vector<die>;

/// Create a number of random dice
dice create_n_random_dice(const int n, std::mt19937& rng_engine);

/// The number of dice used in the game
constexpr int get_n_dice() noexcept { return 8; }

/// Test the dice class
void test_dice();

#endif // DICE_H
