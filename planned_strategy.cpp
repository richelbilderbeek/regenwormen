#include "planned_strategy.h"

#include "probability.h"
#include <cassert>

planned_strategy::planned_strategy(const dice& ds)
  : m_dice{ds}
{

}

probabilities calc_probabilities(const game_state& /* gs */, const planned_strategy& ps)
{
  if (!has_worm(ps)) return {{0, 1.0}};
  return {{0, 0.0}};
}

bool has_worm(const planned_strategy& ps)
{
 return has_worm(ps.get_dice());
}

void test_planned_strategy()
{
  // When never selecting a die, one will always have a chance of 100% to get a tile value of zero
  {
    const game_state gs;
    const planned_strategy ps( {} );
    const auto p = calc_probabilities(gs, ps);
    assert(sum_ps_is_approx_one(p));
    assert(static_cast<int>(p.size()) == 1);
    assert(p.find(0)->second == 1.0);
  }
  // When selecting only a non-worm, one will always have a chance of 100% to get a tile value of zero
  {
    const game_state gs;
    const planned_strategy ps( { die::one } );
    const auto p = calc_probabilities(gs, ps);
    assert(sum_ps_is_approx_one(p));
    assert(static_cast<int>(p.size()) == 1);
    assert(p.find(0)->second == 1.0);
  }
  // When selecting only a worm,
  // there is:
  //
  if (1 == 2)
  {
    const game_state gs;
    const planned_strategy ps( { die::worm } );
    const auto p = calc_probabilities(gs, ps);
    assert(sum_ps_is_approx_one(p));
    assert(p.find(0)->second  == calc_p_x_same_of_n_dice(0, 8));
    assert(p.find(5)->second  == calc_p_x_same_of_n_dice(1, 8));
    assert(p.find(10)->second == calc_p_x_same_of_n_dice(2, 8));
    assert(p.find(15)->second == calc_p_x_same_of_n_dice(3, 8));
    assert(p.find(20)->second == calc_p_x_same_of_n_dice(4, 8));
    assert(p.find(25)->second == calc_p_x_same_of_n_dice(5, 8));
    assert(p.find(30)->second == calc_p_x_same_of_n_dice(6, 8));
    assert(p.find(35)->second == calc_p_x_same_of_n_dice(7, 8));
    assert(p.find(40)->second == calc_p_x_same_of_n_dice(8, 8));
  }
}
