#include "dice_selections.h"

#include "tile.h"

#include <cassert>

int count_n_dice(const dice_selections& dss) noexcept
{
  int n{0};
  for (const auto& ds: dss)
  {
    n += get_size(ds);
  }
  return n;
}

dice_selections create_test_dice_selections(const int value)
{
  constexpr int min_value{1 * get_min_dice_value()};
  constexpr int max_value{get_n_dice() * get_max_dice_value()};
  assert(value >= min_value);
  assert(value <= max_value);

  // Roll as much worms to get at or closest to the value
  const int n_worms_needed{value / 5};
  const dice_selection first_dice_selection(die::worm, n_worms_needed);
  const int remainder = value - get_summed_value(first_dice_selection);
  dice_selections rolls;
  rolls.push_back(first_dice_selection);
  if (remainder != 0)
  {
    const dice_selection second_dice_selection(get_die_with_value(remainder), 1);
    rolls.push_back(second_dice_selection);
  }
  return rolls;
}

int get_total_value(const dice_selections& dss)
{
  if (!has_rolled_worms(dss)) return 0;
  int sum = 0;
  for (const auto& ds: dss)
  {
    sum += get_summed_value(ds);
  }
  return sum;
}

bool has_rolled_worms(const dice_selections& rs) noexcept
{
  for (const auto& r: rs)
  {
    if (has_worms(r)) return true;
  }
  return false;
}

void test_dice_selections()
{
  // An empty dice_selections has no worms
  {
    const dice_selections rs;
    assert(!has_rolled_worms(rs));
  }
  // Create a testing turn
  {
    const auto value = get_lowest_tile_value();
    const auto ds = create_test_dice_selections(value);
    assert(get_total_value(ds) == value);
  }
  // No worms is no value
  {
    const dice_selections dss(1, dice_selection(die::one, 1));
    assert(get_total_value(dss) == 0);
  }
  // An empty set of dice selections has zero dice
  {
    const dice_selections dss;
    assert(count_n_dice(dss) == 0);
  }
  // A set of one dice selection of one dice has one dice
  {
    const dice_selections dss(1, dice_selection(die::one, 1));
    assert(count_n_dice(dss) == 1);
  }
  // A set of two dice selection of two dice has four dice
  {
    const dice_selections dss = {
      dice_selection(die::one, 2),
      dice_selection(die::two, 2),
    };
    assert(count_n_dice(dss) == 4);
  }
}
