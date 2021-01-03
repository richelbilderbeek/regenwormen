#include "dice.h"

#include "probability.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <sstream>
#include <iostream>

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
  return get_all_permutations_for_subset(get_all_die_symbols());
}

std::vector<dice> get_all_permutations_for_subset(dice ds)
{
  std::vector<dice> dss;
  dss.reserve(factorial(ds.size() + 1)); //An approximation

  // Get all the permutations for this subset
  dss.push_back(ds);
  while (next_permutation(begin(ds), end(ds)))
  {
    dss.push_back(ds);
  }

  // Get all the permutations for all sub-sub set
  const int n_dice = ds.size();

  // No use to make subsets for zero dice
  if (n_dice == 1) return dss;

  for (int i = 0; i != n_dice; ++i)
  {
    // Create a sub-sub set with the ith die removed
    dice sub_ds = ds;
    sub_ds.erase(sub_ds.begin() + i);
    assert(sub_ds.size() == ds.size() - 1);
    const std::vector<dice> sub_dss = get_all_permutations_for_subset(sub_ds);
    // Copy all those that have 1 less element
    std::copy_if(
      std::begin(sub_dss),
      std::end(sub_dss),
      std::back_inserter(dss),
      [n_dice](const dice& sub_dc) { return static_cast<int>(sub_dc.size()) == n_dice - 1; }
    );
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

std::string to_str(const dice& ds)
{
  std::stringstream s;
  std::copy(std::begin(ds), std::end(ds), std::ostream_iterator<die>(s, " "));
  std::string str = s.str();
  if (str.back() == ' ') str.pop_back();
  return str;
}

std::ostream& operator<<(std::ostream& os, const dice& ds)
{
  os << to_str(ds);
  return os;
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
    /*
    const auto streaks = get_all_permutations();
    // There are 6! = 720 streaks
    constexpr int expected_size{
        factorial(6)
      + factorial(5)
      + factorial(4)
      + factorial(3)
      + factorial(2)
      + factorial(1)
    };
    assert(static_cast<int>(streaks.size()) == expected_size);
    */
  }
  // to_str
  {
    const dice ds = { die::one, die::worm, die::two };
    const std::string expected{"1 W 2"};
    const std::string actual{to_str(ds)};
    assert(actual == expected);
  }
  // operator<<
  {
    const dice ds = { die::one, die::worm };
    std::stringstream s;
    s << ds;
    const std::string expected{to_str(ds)};
    const std::string actual = s.str();
    assert(actual == expected);

  }
}
