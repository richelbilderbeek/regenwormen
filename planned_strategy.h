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

  /// These dice throws will be selected
  const auto& get_dice() const noexcept { return  m_dice; }

private:
  /// These dice throws will be selected
  dice m_dice;
};

/// Calculate the expected payoff by playing a certain set strategy in a certain game state
double calc_payoff(const game_state& gs, const planned_strategy& ps);

/// Calculate the probabilities to obtain each value for a pre-planned strategy
probabilities calc_probabilities(const game_state& gs, const planned_strategy& ps);

/// Get all (useful) planned strategies
std::vector<planned_strategy> get_all_planned_strategies();

/// Is there a die symbols selection with a worm?
/// If not, it is 100% expected to obtain a value of zero
bool has_worm(const planned_strategy& ps);

/// Test the planned strategy class
void test_planned_strategy();

std::string to_str(const planned_strategy& ps);

std::ostream& operator<<(std::ostream& os, const planned_strategy& ps);

#endif // PLANNED_STRATEGY_H
