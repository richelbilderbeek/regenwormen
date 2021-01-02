#ifndef DICE_ROLL_H
#define DICE_ROLL_H

#include "dice.h"

/// A dice roll
class dice_roll
{
public:
  dice_roll(
    const dice& current_roll,
    const dice& past_picks
  );
};

/// Test the dice_roll class
void test_dice_roll();

#endif // DICE_ROLL_H
