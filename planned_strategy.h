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

  const auto& get_dice() const noexcept { return  m_dice; }

private:
  dice m_dice;
};

/// Calculate the probabilities to obtain each value for a pre-planned strategy
probabilities calc_probabilities(const game_state& gs, const planned_strategy& ps);



/// Is there a die symbols selection with a worm?
/// If not, it is 100% expected to obtain a value of zero
bool has_worm(const planned_strategy& ps);

/// Test the planned strategy class
void test_planned_strategy();

#endif // PLANNED_STRATEGY_H
