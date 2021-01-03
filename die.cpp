#include "die.h"

#include <cassert>
#include <random>
#include <sstream>

die create_random_die(std::mt19937& rng_engine)
{
  std::uniform_int_distribution d(0, 5);
  return static_cast<die>(d(rng_engine));
}

std::vector<die> get_all_die_symbols() noexcept
{
  return
  {
    die::one,
    die::two,
    die::three,
    die::four,
    die::five,
    die::worm
  };
}

die get_die_with_value(const int value)
{
  switch (value)
  {
    case 1: return die::one;
    case 2: return die::two;
    case 3: return die::three;
    case 4: return die::four;
    default:
      assert(value == 5);
      return die::five;
  }
}

std::string to_str(const die d) noexcept
{
  switch (d)
  {
    case die::one: return "1";
    case die::two: return "2";
    case die::three: return "3";
    case die::four: return "4";
    case die::five: return "5";
    case die::worm:
    default:
      return "W";
  }
}

std::ostream& operator<<(std::ostream& os, const die d) noexcept
{
  os << to_str(d);
  return os;
}

void test_die()
{
  static_assert (get_min_dice_value() == 1, "the one is the lowest symbol on a die");
  static_assert (get_max_dice_value() == 5, "a worm also has a value of 5");
  static_assert (get_die_value(die::one) == 1, "a one has a value of 1");
  static_assert (get_die_value(die::two) == 2, "a two has a value of 2");
  static_assert (get_die_value(die::three) == 3, "a three has a value of 3");
  static_assert (get_die_value(die::four) == 4, "a four has a value of 4");
  static_assert (get_die_value(die::five) == 5, "a five has a value of 5");
  static_assert (get_die_value(die::worm) == 5, "a worm has a value of 5");
  // One can roll each symbol, will freeze the program if this fails
  {
    const auto all_die_symbols{get_all_die_symbols()};
    assert(all_die_symbols.size() == 6);
    std::mt19937 rng_engine;
    for (const auto d: all_die_symbols)
    {
      while (create_random_die(rng_engine) != d) {}
    }
  }
  // to_str
  {
    assert(to_str(die::one) == "1");
    assert(to_str(die::two) == "2");
    assert(to_str(die::three) == "3");
    assert(to_str(die::four) == "4");
    assert(to_str(die::five) == "5");
    assert(to_str(die::worm) == "W");
  }
  // to_str
  {
    std::stringstream s;
    s << die::one;
    assert(s.str() == "1");
  }
}
