#include "action.h"

#include <cassert>
#include <sstream>

void test_action()
{
  static_assert(create_roll_dice_action().get_type() == action_type::roll_dice);
  static_assert(create_select_dice_action().get_type() == action_type::select_dice);
  static_assert(create_select_dice_action(die::two).get_die() == die::two);
  static_assert(create_pick_tile_action().get_type() == action_type::pick_tile);
  static_assert(create_pick_tile_action(21).get_tile_value() == 21);
  static_assert(create_pass_action().get_type() == action_type::pass);
  // to_str
  {
    assert(to_str(create_roll_dice_action()) == "roll dice");
    assert(to_str(create_select_dice_action(die::two)) == "select dice with symbol 2");
    assert(to_str(create_pick_tile_action(21)) == "pick tile with value 21");
    assert(to_str(create_pass_action()) == "pass");
  }
  // operator<<
  {
    std::stringstream s;
    s << create_pass_action();
    assert(s.str() == "pass");
  }
}

std::string to_str(const action& a) noexcept
{
  if (a.get_type() == action_type::pass) return "pass";
  if (a.get_type() == action_type::roll_dice) return "roll dice";
  if (a.get_type() == action_type::select_dice) return "select dice with symbol " + to_str(a.get_die());
  assert(a.get_type() == action_type::pick_tile);
  return "pick tile with value " + std::to_string(a.get_tile_value());
}

std::ostream& operator<<(std::ostream& os, const action& a) noexcept
{
  os << to_str(a);
  return os;
}
