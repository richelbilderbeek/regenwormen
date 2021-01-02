#ifndef ACTION_H
#define ACTION_H

#include "action_type.h"
#include "die.h"

/// An action to apply to a game_state
class action
{
public:
  constexpr action(
    const action_type t,
    const die d = die::worm,
    const int tile_value = 0
  ) : m_t{t},
      m_d{d},
      m_tile_value{tile_value}
  {

  }

  constexpr action_type get_type() const noexcept { return m_t; }
  constexpr auto get_die() const noexcept { return m_d; }
  constexpr auto get_tile_value() const noexcept { return m_tile_value; }

private:
  action_type m_t;
  die m_d;
  int m_tile_value;
};

/// Get the action to give up, to say 'your turn' to the other player(s)
constexpr action create_pass_action()
{
  return action(action_type::pass);
}

/// Get the action to pick a tile of a value.
/// This value must be at least the sum of the previously selected dice
constexpr action create_pick_tile_action(const int tile_value = 21)
{
  return action(action_type::pick_tile, die::worm, tile_value);
}

/// Get the action to roll the dice
constexpr action create_roll_dice_action()
{
  return action(action_type::roll_dice);
}

/// Get the action to select dice of a certain value, remove the dice from the table
constexpr action create_select_dice_action(const die d = die::worm)
{
  return action(action_type::select_dice, d);
}

/// Test the action class
void test_action();

#endif // ACTION_H
