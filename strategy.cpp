#include "strategy.h"

#include <algorithm>
#include <cassert>

std::vector<action> create_all_actions()
{
  std::vector<action> actions;
  actions.push_back(create_pass_action());
  actions.push_back(create_roll_dice_action());
  for (const die d: get_all_die_symbols())
  {
    actions.push_back(create_select_dice_action(d));
  }
  for (int i = get_lowest_tile_value(); i != get_highest_tile_value() + 1; ++i) // +1 to include highest tile value
  {
    actions.push_back(create_pick_tile_action(i));
  }
  return actions;
}

std::vector<action> create_all_valid_actions(const game_state& s)
{
  using namespace std;
  const auto all_actions = create_all_actions();
  std::vector<action> valid_actions;
  copy_if(
    begin(all_actions),
    end(all_actions),
    back_inserter(valid_actions),
    [s](const action& a) { return can_do_action(s, a); }
  );
  return valid_actions;
}

action get_best_action(const game_state& s)
{
  return create_roll_dice_action();
}

void test_get_best_action()
{
  // If there are no dice rolled, roll the dice
  {
    // The initial game state
    const game_state s;
    assert(get_best_action(s).get_type() == action_type::roll_dice);
  }
  // Create all actions
  {
    const auto as = create_all_actions();
    // 1: roll dice
    // 1: pass
    // 6: select a die symbol
    // 16: pick a tile
    assert(static_cast<int>(as.size()) == 1 + 1 + 6 + 16);
  }
  // If there are no dice rolled, there are two actions
  {
    const game_state s;
    // 1: roll dice
    // 1: pass
    assert(static_cast<int>(create_all_valid_actions(s).size()) == 2);
  }
}
