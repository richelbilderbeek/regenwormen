#ifndef DICE_OCCURANCE_H
#define DICE_OCCURANCE_H

#include <vector>

/// How often does a dice occur in a dice roll?
using dice_occurance = int;

/// Get all the options at
std::vector<dice_occurance> get_dice_occurances();


void test_dice_occurance();

#endif // DICE_OCCURANCE_H
