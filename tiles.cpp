#include "tiles.h"

#include <algorithm>
#include <cassert>

bool can_get_tile(const tiles& ts, const int value)
{
  for (const auto& t: ts)
  {
    if (get_value(t) == value) return true;
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

int get_n_worms(const tiles& ts) noexcept
{
  using namespace std;
  int n_worms = 0;
  for (const auto& t: ts)
  {
    n_worms += get_n_worms(t);
  }
  return n_worms;
}

bool has_tile_with_value(const tiles& ts, const int tile_value) noexcept
{
  using namespace std;
  return count_if(
    begin(ts),
    end(ts),
    [tile_value](const auto& t)
    {
      return t.get_value() == tile_value;
    }
  );
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
  // The 16 tiles have 4 + 8 + 12 + 16 = 40 worms
  {
    const auto tiles = create_all_tiles();
    assert(get_n_worms(tiles) == 4 + 8 + 12 + 16);
  }
}
