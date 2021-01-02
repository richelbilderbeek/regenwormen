#include "turn.h"

#include "tile.h"

#include <cassert>

turn::turn(
  const dice_selections& dice_selections,
  const int picked_tile_value
) : m_dice_selections{dice_selections},
    m_picked_tile_value{picked_tile_value}
{
  // Cannot pick a tile higher than the value of the dice selections
  // Note: dice selections without a worm have a value of zero
  assert(m_picked_tile_value <= get_total_value(*this));
}

turn create_test_turn(const int value)
{
  const auto dss{create_test_dice_selections(value)};
  return turn(dss, get_summed_value(dss));
}

int get_total_value(const turn& t)
{
  return get_total_value(t.get_dice_selections());
}

void test_turn()
{
  // At the start of a turn, there have been no dice rolls
  {
    const turn t = create_test_turn();
    assert(!t.get_dice_selections().empty());
  }
  // Create a testing turn
  {
    const auto value = get_lowest_tile_value();
    const auto turn = create_test_turn(value);
    assert(get_total_value(turn) == value);
  }
  // No worms is no value
  {
    const dice_selections ds(1, dice_selection(die::one, 1));
    const turn t(ds);
    assert(get_total_value(t) == 0);
  }
  // One can pick a tile with a lower value than thrown
  {
    const int picked_value{get_lowest_tile_value()};
    const turn t(
      create_test_dice_selections(get_highest_tile_value()),
      picked_value
    );
    assert(t.get_picked_tile_value() == picked_value);
  }
}
