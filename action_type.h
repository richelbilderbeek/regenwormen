#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

/// The type of actions
enum class action_type
{
  roll_dice, // Roll the dice
  select_dice, // Select dice of a certain value, remove the dice from the table
  pick_tile, // Pick a tile of a value. This value must be at least the sum of the previously selected dice
  pass // Give up, say 'your turn' to the other player(s)
};

void test_action_type();

#endif // ACTION_TYPE_H
