#include "tiles.h"

#include <algorithm>
#include <cassert>

bool can_get_tile(const tiles& ts, const int value)
{
  for (const auto& t: ts)
  {
    if (get_die_value(t) == value) return true;
  }
  return false;
}

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

void remove_tile_with_value(
  tiles& ts,
  const int value
)
{
  using namespace std;
  const auto iter = remove_if(
    begin(ts), end(ts),
    [value](const auto& t) { return value == t.get_value(); }
  );
  assert(iter != end(ts));
  ts.erase(iter, end(ts));
}

void test_tiles()
{
  // A standard game has 16 tiles
  {
    const auto tiles = create_all_tiles();
    assert(tiles.size() == 16);
  }
  // Removing the 21 tile can be done
  {
    auto ts = create_all_tiles();
    assert(ts.size() == 16);
    remove_tile_with_value(ts, 21);
    assert(ts.size() == 15);
  }
}
