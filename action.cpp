#include "action.h"

void test_action()
{
  static_assert(create_roll_dice_action().get_type() == action_type::roll_dice);
  static_assert(create_select_dice_action().get_type() == action_type::select_dice);
  static_assert(create_select_dice_action(die::two).get_die() == die::two);
  static_assert(create_pick_tile_action().get_type() == action_type::pick_tile);
  static_assert(create_pick_tile_action(21).get_tile_value() == 21);
  static_assert(create_pass_action().get_type() == action_type::pass);
}
