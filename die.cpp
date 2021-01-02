#include "die.h"

#include <cassert>

die get_die_with_value(const int value)
{
  switch (value)
  {
    case 1: return die::one;
    case 2: return die::two;
    case 3: return die::three;
    case 4: return die::four;
    default:
      assert(value == 5);
      return die::five;
  }
}

void test_die()
{
  static_assert (get_min_dice_value() == 1, "the one is the lowest symbol on a die");
  static_assert (get_max_dice_value() == 5, "a worm also has a value of 5");
  static_assert (get_die_value(die::one) == 1, "a one has a value of 1");
  static_assert (get_die_value(die::two) == 2, "a two has a value of 2");
  static_assert (get_die_value(die::three) == 3, "a three has a value of 3");
  static_assert (get_die_value(die::four) == 4, "a four has a value of 4");
  static_assert (get_die_value(die::five) == 5, "a five has a value of 5");
  static_assert (get_die_value(die::worm) == 5, "a worm has a value of 5");
}