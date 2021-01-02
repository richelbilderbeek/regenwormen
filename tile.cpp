#include "tile.h"

#include <cassert>

tile::tile(const int value)
  : m_value{value}
{

}

void test_tile()
{
  static_assert(get_lowest_tile_value() == 21);
  static_assert(get_highest_tile_value() == 36);
}
