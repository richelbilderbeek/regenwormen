#ifndef TILE_H
#define TILE_H

/// A tile
class tile
{
public:
  /// Create a tile
  /// @param value the number on the tile
  tile(const int value);

private:

  int m_value;
};

/// Get the lowest valid tile value
constexpr int get_lowest_tile_value() { return 21; }

/// Get the highest valid tile value
constexpr int get_highest_tile_value() { return 36; }

/// Test the tile class
void test_tile();

#endif // TILE_H
