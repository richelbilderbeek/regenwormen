#include "dice.h"

#include "probability.h"
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

std::vector<dice> get_all_permutations()
{
  std::vector<dice> dss;
  dss.reserve(factorial(6));

  std::vector<die> ds = get_all_die_symbols();
  dss.push_back(ds);

  while (next_permutation(begin(ds), end(ds)))
  {
    dss.push_back(ds);
  }
  return dss;
}

bool has_die_with_symbol(const dice& d, const die symbol)
{
  using namespace std;
  return count(begin(d), end(d), symbol);
}

bool has_worm(const dice& ds) noexcept
{
  return has_die_with_symbol(ds, die::worm);
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
    const auto streaks = get_all_permutations();
    // There are 6! = 720 streaks
    assert(static_cast<int>(streaks.size()) == factorial(6));
    for (int i = 0; i != factorial(6); ++i)
    {
      assert(has_die_with_symbol(streaks[i], die::one));
      assert(has_die_with_symbol(streaks[i], die::two));
      assert(has_die_with_symbol(streaks[i], die::three));
      assert(has_die_with_symbol(streaks[i], die::four));
      assert(has_die_with_symbol(streaks[i], die::five));
      assert(has_die_with_symbol(streaks[i], die::worm));
    }
  }
}
