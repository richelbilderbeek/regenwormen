#ifndef PLANNED_STRATEGY_H
#define PLANNED_STRATEGY_H

#include "game_state.h"
#include "dice.h"
#include "probabilities.h"
#include <vector>

/// A planned strategy is the strategy that is determined before the first dice throw
class planned_strategy
{
public:
  // The dice throws are determined beforehand
  planned_strategy(const dice& ds);

private:
  dice m_dice;
};

/// Calculate the probabilities to obtain each value for a pre-planned strategy
probabilities calc_probabilities(const game_state& gs, const planned_strategy& ps);



/// Test the planned strategy class
void test_planned_strategy();

#endif // PLANNED_STRATEGY_H
