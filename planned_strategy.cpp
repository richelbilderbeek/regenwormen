#include "planned_strategy.h"

#include "probability.h"
#include "dice_occurances.h"

#include <cassert>

planned_strategy::planned_strategy(const dice& ds)
  : m_dice{ds}
{

}

probabilities calc_probabilities(const game_state& gs, const planned_strategy& ps)
{
  if (!has_worm(ps)) return {{0, 1.0}};

  //Assume a clean slate for now
  assert(gs.get_dice().empty());
  assert(gs.get_dice_selections().empty());

  // No need to throw dice here: this is already known by the strategist

  /// Create all the valid dice occurances for the planned number of throws
  const std::vector<dice_occurances> doss = create_all_dice_occurances_for_n_throws(
    ps.get_dice().size()
  );

  // For each of these occurances, we know the tile we'll land on
  const std::vector<int> tile_values = calc_all_tile_values(
    ps.get_dice(), // the predetermined dice throw, always the same
    doss // The occurances of these dice
  );
  assert(doss.size() == tile_values.size());

  // The probabilities for each occurance
  const std::vector<double> dice_occurance_probabilities = get_probabilities(doss);
  assert(doss.size() == dice_occurance_probabilities.size());
  const double sum_dice_occurance_probabilities = std::accumulate(
    std::begin(dice_occurance_probabilities),
    std::end(dice_occurance_probabilities),
    0.0
  );
  assert(is_approx_one(sum_dice_occurance_probabilities));

  // Sum the probabilities to land on each tile
  probabilities probs;
  const int n = doss.size();
  for (int i = 0; i != n; ++i)
  {
    const int tile_value{tile_values[i]};
    const double p{dice_occurance_probabilities[i]};
    if (probs.find(tile_value) == std::end(probs))
    {
      probs.insert(std::pair(tile_value, p));
    }
    else
    {
      probs[tile_value] += p;
    }
  }

  return probs;
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
  // the probabilities of each tile value is easy to calculate
  //
  {
    const game_state gs;
    const planned_strategy ps( { die::worm } );
    const auto p = calc_probabilities(gs, ps);
    const auto sum_p = sum_probabilities(p);
    assert(is_approx_one(sum_p));
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
  // When determined to play a worm, then a 5,
  // the probabilities of each tile value is harder to calculate
  //
  {
    const game_state gs;
    const planned_strategy ps( { die::worm, die::five } );
    const auto p = calc_probabilities(gs, ps);
    const auto sum_p = sum_probabilities(p);
    assert(is_approx_one(sum_p));
    assert(p.find(0)->second > 0.0);
    assert(p.find(1) == std::end(p));
    assert(p.find(5)->second > 0.0);
    assert(p.find(10)->second > 0.0);
    assert(p.find(15)->second > 0.0);
    assert(p.find(20)->second > 0.0);
    assert(p.find(25)->second > 0.0);
    assert(p.find(30)->second > 0.0);
    assert(p.find(35)->second > 0.0);
    assert(p.find(40)->second > 0.0);
  }
  // When determined to play a worm, then a 5, then a 4
  // the probabilities of each tile value is harder to calculate
  //
  {
    const game_state gs;
    const planned_strategy ps( { die::worm, die::five, die::four } );
    const auto p = calc_probabilities(gs, ps);
    const auto sum_p = sum_probabilities(p);
    assert(is_approx_one(sum_p));
    assert(p.find(0)->second > 0.0);
    assert(p.find(1) == std::end(p));
    assert(p.find(2) == std::end(p));
    assert(p.find(3) == std::end(p));
    assert(p.find(4)->second > 0.0);
    assert(p.find(5)->second > 0.0);
    assert(p.find(6) == std::end(p));
    assert(p.find(7) == std::end(p));
    assert(p.find(8)->second > 0.0);
    assert(p.find(9)->second > 0.0);
    assert(p.find(10)->second > 0.0);
    assert(p.find(11) == std::end(p));
    assert(p.find(12)->second > 0.0);
    assert(p.find(13) == std::end(p));
    assert(p.find(14)->second > 0.0);
    assert(p.find(15)->second > 0.0);
    assert(p.find(16)->second > 0.0);
    assert(p.find(17) == std::end(p));
    assert(p.find(18)->second > 0.0);
    assert(p.find(19)->second > 0.0);
    assert(p.find(20)->second > 0.0);
    assert(p.find(25)->second > 0.0);
    assert(p.find(30)->second > 0.0);
    assert(p.find(35)->second > 0.0);
    assert(p.find(40)->second > 0.0);
  }
}
