#include "tile.h"

#include <cassert>
#include <sstream>

tile::tile(const int value)
  : m_value{value}
{

}

std::string to_str(const tile& t)
{
  std::stringstream ss;
  ss << get_value(t) << "|" << std::string(get_n_worms(t), 'W');
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const tile& t)
{
  os << to_str(t);
  return os;
}

void test_tile()
{
  static_assert(get_lowest_tile_value() == 21);
  static_assert(get_highest_tile_value() == 36);
  static_assert(get_n_worms(21) == 1);
  static_assert(get_n_worms(22) == 1);
  static_assert(get_n_worms(23) == 1);
  static_assert(get_n_worms(24) == 1);
  static_assert(get_n_worms(25) == 2);
  static_assert(get_n_worms(26) == 2);
  static_assert(get_n_worms(27) == 2);
  static_assert(get_n_worms(28) == 2);
  static_assert(get_n_worms(29) == 3);
  static_assert(get_n_worms(30) == 3);
  static_assert(get_n_worms(31) == 3);
  static_assert(get_n_worms(32) == 3);
  static_assert(get_n_worms(33) == 4);
  static_assert(get_n_worms(34) == 4);
  static_assert(get_n_worms(35) == 4);
  static_assert(get_n_worms(36) == 4);

  // A tile must store its value
  {
    const int value{get_lowest_tile_value()};
    const tile t(value);
    assert(value == t.get_value());
  }
  // tile::get_value is the same as get_value(tile)
  {
    const int value{get_lowest_tile_value()};
    const tile t(value);
    assert(get_value(t) == value);
  }
  // to_str
  {
    assert(to_str(tile(21)) == "21|W");
    assert(to_str(tile(36)) == "36|WWWW");
  }
  // operator<<
  {
    std::stringstream s;
    s << tile(21);
    assert(s.str() == "21|W");
  }
}
