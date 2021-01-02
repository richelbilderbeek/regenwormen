#include "strategy.h"

#include <cassert>

action get_best_action(const game_state& s)
{
  return create_roll_dice_action();
}

void test_get_best_action()
{
  // If there is hope (whatever that is), and there are no dice rolled, roll the dice
  {
    // The initial game state
    const game_state s;
    assert(get_best_action(s).get_type() == action_type::roll_dice);
  }
}
