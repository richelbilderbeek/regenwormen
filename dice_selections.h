#ifndef DICE_SELECTIONS_H
#define DICE_SELECTIONS_H

#include "dice_selection.h"
#include <vector>

/// A collection of dice rolls
using dice_selections = std::vector<dice_selection>;

/// Count the number of dice in all selections combined
int count_n_dice(const dice_selections& dss) noexcept;

/// Create any valid collection of dice selections
/// to get to a specific total value.
/// Will throw if the value cannot be reached, e.g. 1 and 100
dice_selections create_test_dice_selections(const int value);

/// Get the total value of multiple dice selections.
/// The value of a turn is zero if no worms have been rolled
int get_total_value(const dice_selections& dss);

/// Get the summed value of the selections
// Not alphabetic, as it depends on the declaration of another function
// inline to prevent compile errors
inline int get_summed_value(const dice_selections& dss) noexcept { return get_total_value(dss); }

/// Is there at least one dice_selection with a worm?
bool has_rolled_worms(const dice_selections& dss) noexcept;

/// Test the dice_selections class
void test_dice_selections();

#endif // DICE_SELECTIONS_H
