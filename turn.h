#ifndef TURN_H
#define TURN_H

#include "dice_selections.h"

/// A turn is a collection of dice selections
/// as well as the picked tile
class turn
{
public:
  /// Create a turn, with or without a picked tile
  /// @param ds the collection of dice selections
  /// @param picked_tile_value the value of the picked tile. This
  ///   value is either the summed value of the dice selections,
  ///   or lower (in the case a tile with that value could not be picked, but a tile with
  ///   lower value could). A value of zero denotes that no tile was taken
  turn(
    const dice_selections& ds,
    const int picked_tile_value = 0
  );

  const auto& get_dice_selections() const noexcept { return m_dice_selections; }
  auto get_picked_tile_value() const noexcept { return m_picked_tile_value; }

private:
  dice_selections m_dice_selections;
  int m_picked_tile_value;

};

/// Create any valid turn of a specific total value
/// Will throw if the value cannot be reached, e.g. 1 and 100
turn create_test_turn(const int value = 5);

/// Get the total value of a turn.
/// The value of a turn is zero if no worms have been rolled
int get_total_value(const turn& t);

/// Test the turn class
void test_turn();

#endif // TURN_H
