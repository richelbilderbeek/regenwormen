#include "tiles.h"
#include <cassert>


tiles create_all_tiles() noexcept
{
  std::vector<tile> tiles;
  const int min = get_lowest_tile_value();
  const int max = get_highest_tile_value() + 1; // Include the highest tile value
  for (int i = min; i != max; ++i)
  {
    tiles.push_back(tile(i));
  }
  assert(tiles.size() == 16);
  return tiles;
}

void test_tiles()
{
  // A standard game has 16 tiles
  {
    const auto tiles = create_all_tiles();
    assert(tiles.size() == 16);
  }
}
