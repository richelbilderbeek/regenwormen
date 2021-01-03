#include "planned_strategy.h"

#include <cassert>

planned_strategy::planned_strategy(const dice& ds)
  : m_dice{ds}
{

}

probabilities calc_probabilities(const game_state& /* gs */, const planned_strategy& /* ps */)
{
  return {{0, 1.0}};
}

void test_planned_strategy()
{
  // When never selecting a die, one will always have a chance of 100% to get a tile value of zero
  {
    const game_state gs;
    const planned_strategy ps( {} );
    const auto p = calc_probabilities(gs, ps);
    assert(probabilities_sum_up_to_approx_one(p));
  }
  // When selecting only a worm,
  // there is:
  //
  {
    const game_state gs;
    const planned_strategy ps( { die::worm } );
    const auto p = calc_probabilities(gs, ps);
    assert(probabilities_sum_up_to_approx_one(p));
  }
}
