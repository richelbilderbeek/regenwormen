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
  dss.reserve(1956); //For 6 dice

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
    std::copy(
      std::begin(sub_dss),
      std::end(sub_dss),
      std::back_inserter(dss)
      //[n_dice = sub_ds.size()](const dice& sub_dc) { return sub_dc.size()== n_dice; }
    );
  }

  std::sort(std::begin(dss), std::end(dss));
  auto last = std::unique(std::begin(dss), std::end(dss));
  dss.erase(last, std::end(dss));


  return dss;
}

std::vector<dice> get_all_useful_permutations()
{
  const auto ps = get_all_permutations();
  std::vector<dice> useful_ps;
  std::copy_if(
    std::begin(ps), std::end(ps),
    std::back_inserter(useful_ps),
    [](const auto& d) { return has_worm(d); }
  );
  return useful_ps;
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
    const auto streaks = get_all_permutations();
    // Subset of 6 different die symbols
    {
      // There are 6! = 720 streaks that have six die symbols
      const int expected_n{
        factorial(6) *
        binomial_coefficient(6, 6)
      };
      //const int expected_n{factorial(6)};
      const int actual_n = std::count_if(
        std::begin(streaks),
        std::end(streaks),
        [](const auto& s) { return s.size() == 6; }
      );
      assert(actual_n == expected_n);
    }
    // All subset of 5 different die symbols
    {
      // There are 5! * binomial_coefficient(6, 5) = 720 streaks that have five die symbols,
      //
      const int expected_n{
        factorial(5) *
        binomial_coefficient(6, 5)
      };
      const int actual_n = std::count_if(
        std::begin(streaks),
        std::end(streaks),
        [](const auto& s) { return s.size() == 5; }
      );
      assert(actual_n == expected_n);
    }
    // All subset of 4 different die symbols
    {
      // There are 4! * binomial_coefficient(6, 4) = 360 streaks that have four die symbols,
      //
      const int expected_n{
        factorial(4) *
        binomial_coefficient(6, 4)
      };
      const int actual_n = std::count_if(
        std::begin(streaks),
        std::end(streaks),
        [](const auto& s) { return s.size() == 4; }
      );
      assert(actual_n == expected_n);
    }
    // All subset of 3 different die symbols
    {
      // There are 3! * binomial_coefficient(6, 3) = 120 streaks that have four die symbols,
      //
      const int expected_n{
        factorial(3) *
        binomial_coefficient(6, 3)
      };
      const int actual_n = std::count_if(
        std::begin(streaks),
        std::end(streaks),
        [](const auto& s) { return s.size() == 3; }
      );
      assert(actual_n == expected_n);
    }
    // All subset of 2 different die symbols
    {
      // There are 2! * binomial_coefficient(6, 2) = 30 streaks that have four die symbols,
      //
      const int expected_n{
        factorial(2) *
        binomial_coefficient(6, 2)
      };
      const int actual_n = std::count_if(
        std::begin(streaks),
        std::end(streaks),
        [](const auto& s) { return s.size() == 2; }
      );
      assert(actual_n == expected_n);
    }
    // All subset of 1 different die symbols
    {
      // There are 1! * binomial_coefficient(6, 1) = ? streaks that have one die symbols,
      //
      const int expected_n{
        factorial(1) *
        binomial_coefficient(6, 1)
      };
      const int actual_n = std::count_if(
        std::begin(streaks),
        std::end(streaks),
        [](const auto& s) { return s.size() == 1; }
      );
      assert(actual_n == expected_n);
      assert(actual_n == 6);
    }
    constexpr int expected_size{
        (factorial(6) * binomial_coefficient(6, 6))
      + (factorial(5) * binomial_coefficient(6, 5))
      + (factorial(4) * binomial_coefficient(6, 4))
      + (factorial(3) * binomial_coefficient(6, 3))
      + (factorial(2) * binomial_coefficient(6, 2))
      + (factorial(1) * binomial_coefficient(6, 1))
    };
    static_assert(expected_size == 1956);
    assert(static_cast<int>(streaks.size()) == expected_size);
  }
  {
    const auto ps = get_all_useful_permutations();
    assert(ps.size() == 1631);
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
