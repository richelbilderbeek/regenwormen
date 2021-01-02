#include "dice_selection.h"

#include <cassert>

dice_selection create_test_dice_selection(const die d, const int n)
{
  return dice_selection(d, n);
}


void test_dice_selection()
{
  static_assert(get_size(dice_selection(die::worm, 2)) == 2);
  static_assert(get_die(dice_selection(die::worm, 2)) == die::worm);
  static_assert(has_worms(dice_selection(die::worm, 2)));
  static_assert(!has_worms(dice_selection(die::one, 1)));
  static_assert(get_summed_value(dice_selection(die::one, 1)) == 1);
  static_assert(get_summed_value(dice_selection(die::worm, 2)) == 10);
}
