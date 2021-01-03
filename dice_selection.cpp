#include "dice_selection.h"

#include <cassert>
#include <sstream>

dice_selection create_test_dice_selection(const die d, const int n)
{
  return dice_selection(d, n);
}

std::string to_str(const dice_selection& ds)
{
  std::stringstream ss;
  ss << get_size(ds) << "x " << get_die(ds);
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const dice_selection& ds)
{
  os << to_str(ds);
  return os;
}

void test_dice_selection()
{
  static_assert(get_size(dice_selection(die::worm, 2)) == 2);
  static_assert(get_die(dice_selection(die::worm, 2)) == die::worm);
  static_assert(has_worm(dice_selection(die::worm, 2)));
  static_assert(!has_worm(dice_selection(die::one, 1)));
  static_assert(get_summed_value(dice_selection(die::one, 1)) == 1);
  static_assert(get_summed_value(dice_selection(die::worm, 2)) == 10);
  // create_test_dice_selection
  {
    const auto ds = create_test_dice_selection(die::worm, 8);
    assert(has_worm(ds));
    assert(ds.get_size() == 8);
  }
  {
    assert(to_str(dice_selection(die::one, 2)) == "2x 1");
    assert(to_str(dice_selection(die::worm, 3)) == "3x W");
  }
  {
    std::stringstream s;
    s << dice_selection(die::two, 3);
    assert(s.str() == "3x 2");
  }
}
