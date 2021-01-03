#ifndef DICE_OCCURANCES_H
#define DICE_OCCURANCES_H

#include "dice_occurance.h"

#include <vector>

/// A collection of dice occurances
/// For example:
///   { 8 } : rolled 8 dice that are the same in the first roll
///   { 7, 1 } : rolled 7 dice that are the same in the first roll, then 1
///   { 6, 2 } : rolled 6 same dice in the first roll, then 2 same ones
///   { 6, 1, 1 } : rolled 6 same dice in the first roll, then 1 unique one, then 1 unique one
///   { 6, 1, 1 } : rolled 6 same dice in the first roll, then 1 unique one, then 1 unique one
/// Should always sum op to the number of dice (which is 8)
using dice_occurances = std::vector<dice_occurance>;

/// The number of dice occurrances must sum up to the number of dice (which is 8)
bool sum_up_to_n_dice(const dice_occurances& dos);

/// Test the dice_occurances class
void test_dice_occurances();


#endif // DICE_OCCURANCES_H
