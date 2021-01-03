#ifndef DICE_OCCURANCES_H
#define DICE_OCCURANCES_H

#include "dice.h"
#include "dice_occurance.h"

#include <iosfwd>
#include <vector>

/// A collection of dice occurances
/// For example:
///   { 8 } : rolled 8 dice that are the same in the first roll
///   { 7, 1 } : rolled 7 dice that are the same in the first roll, then 1
///   { 6, 2 } : rolled 6 same dice in the first roll, then 2 same ones
///   { 6, 1, 1 } : rolled 6 same dice in the first roll, then 1 unique one, then 1 unique one
///   { 6, 1, 1 } : rolled 6 same dice in the first roll, then 1 unique one, then 1 unique one
/// Should always sum op to the number of dice (which is 8)
/// Has a length from one (that is, one 8) to and including the number of symbols on a dice (which is 6)
using dice_occurances = std::vector<dice_occurance>;

/// Calculate the tile values, if the dice picks are known, as well of how each is thrown
int calc_tile_value(
  const dice& ds,
  const dice_occurances& dos
);

/// Calculate the tile values, if the dice picks are known,
/// for the known occurances of each symbol per throw
std::vector<int> calc_all_tile_values(
  const dice& ds,
  const std::vector<dice_occurances>& doss
);

/// Get the next dice occurances, in pseudo-numerical order
/// Examples (showing the trailing zeroes):
///    0,0,0,0,0,8 -> 0,0,0,0,1,7
///    0,0,0,0,1,7 -> 0,0,0,0,2,6
///    0,0,0,0,2,6 -> 0,0,0,0,3,5
///    0,0,0,0,3,5 -> 0,0,0,0,4,4
///    0,0,0,0,4,4 -> 0,0,0,0,5,3
///    0,0,0,0,5,3 -> 0,0,0,0,6,2
///    0,0,0,0,6,2 -> 0,0,0,0,7,1
///    0,0,0,0,7,1 -> 0,0,0,1,1,6
dice_occurances get_next_dice_occurances(dice_occurances dos);

/// One can have zero desired die symbols in a throw
/// {1} would be to settle to select 1 dice and then pass
inline dice_occurances get_first_dice_occurances() noexcept { return { 0 }; }

inline dice_occurances get_last_dice_occurances() noexcept { return { 3, 1, 1, 1, 1, 1 }; }

/// Calculate the probability that one can actually use the dice occurances
/// For example, {8} has chance (1/6)^6
double get_probability(const dice_occurances dos);

/// Calculate the probabilities for each dice occurance, to actually be used
/// Simply a vectorized version of 'get_probability'
std::vector<double> get_probabilities(const std::vector<dice_occurances>& doss);

/// Create all the 246 possible valid dice occurances
std::vector<dice_occurances> create_all_dice_occurances();

/// Create all the valid dice occurances that when having decided to throw times
/// For example, if the player has decided upon 1 throw,
/// it may land 1, 2, 3, 4, 5, 6, 7 or 8 times that die symbol
///
std::vector<dice_occurances> create_all_dice_occurances_for_n_throws(const int n);

/// The number of dice occurrances must sum up to the number of dice (which is 8)
bool sum_up_to_n_dice(const dice_occurances& dos);

/// The number of dice occurrances must sum up to the number of dice (which is 8)
/// at most.
bool sum_up_to_n_dice_at_most(const dice_occurances& dos);

/// Test the dice_occurances class
void test_dice_occurances();

std::string to_str(const dice_occurances& dos);

std::ostream& operator<<(std::ostream& os, const dice_occurances& dos);

#endif // DICE_OCCURANCES_H
