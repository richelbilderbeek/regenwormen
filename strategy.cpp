#include "strategy.h"

#include <algorithm>
#include <cassert>

bool can_win(const game_state& s)
{
  // There is not always hope,
  // for example, when the one opponent has all tiles except one:
  // even if the focal player throws the value on the opponent's stack,
  // the opponent will throw a dice on the next turn and end the game.

  // A definite win or loss, as all tiles are gone
  if (s.get_available_tiles().empty())
  {
    const int n_worms_focal_player = get_n_worms(s.get_player_tiles()[0]);
    assert(s.get_player_tiles().size() == 2); // One opponent
    const int n_worms_opponent = get_n_worms(s.get_player_tiles()[1]);
    return n_worms_focal_player > n_worms_opponent;
  }

  if (s.get_available_tiles().size() == 1)
  {
    // simple, yet exact case
    // Option 1: take last available tile
    {
      const int n_worms_focal_player = get_n_worms(s.get_player_tiles()[0])
        + get_n_worms(s.get_available_tiles());
      assert(s.get_player_tiles().size() == 2); // One opponent
      const int n_worms_opponent = get_n_worms(s.get_player_tiles()[1]);
      return n_worms_focal_player > n_worms_opponent;
    }

    // Option 2: take opponents top tile, opponent flips last available tile
  }
  else
  {
    //STUB
    //Assume the opponent has only 4s at his/her stack, assume opponent flips all available tiles
    const int n{get_n_available_tiles(s)};
    const int n_worms_focal_player = get_n_worms(s.get_player_tiles()[0]) + (4 * n);
    const int n_worms_opponent = get_n_worms(s.get_player_tiles()[1]) - (4 * n);
    return n_worms_focal_player > n_worms_opponent;
  }
}

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
  // In the start of the game, there is hope
  {
    const game_state s;
    assert(can_win(s));
  }
}
