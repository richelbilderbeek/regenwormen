#include "dice.h"

#include <algorithm>
#include <cassert>

dice create_n_random_dice(const int n, std::mt19937& rng_engine)
{
  dice ds;
  for (int i = 0; i != n; ++i)
  {
    ds.push_back(create_random_die(rng_engine));
  }
  return ds;
}

bool has_die_with_symbol(const dice& d, const die symbol)
{
  using namespace std;
  return count(begin(d), end(d), symbol);
}

void test_dice()
{
  static_assert(get_n_dice() == 8);
  // One can create a set of 1 random dice
  {
    std::mt19937 rng_engine;
    const int n{1};
    const dice d = create_n_random_dice(n, rng_engine);
    assert(static_cast<int>(d.size()) == n);
  }
  // One can create a set of 8 random dice
  {
    std::mt19937 rng_engine;
    const int n{8};
    const dice d = create_n_random_dice(n, rng_engine);
    assert(static_cast<int>(d.size()) == n);
  }
  // Get all the permutations for n dice
  {
    get_all_permutations_for_n_dice(const int n);

}
