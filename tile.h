#ifndef TILE_H
#define TILE_H

#include <iosfwd>
#include <string>

/// A tile
class tile
{
public:
  /// Create a tile
  /// @param value the number on the tile
  tile(const int value);

  /// Get the value on a tile
  constexpr auto get_value() const noexcept { return m_value; }

private:

  int m_value;
};

/// Get the lowest valid tile value
constexpr int get_lowest_tile_value() { return 21; }

/// Get the highest valid tile value
constexpr int get_highest_tile_value() { return 36; }

/// Get the number of worms on a tile
/// This function assumes a correct value, else returns nonsense
constexpr auto get_n_worms(const int value) noexcept { return 1 + ((value - 21) / 4); }

/// Get the value on a tile
/// Helper function
constexpr auto get_value(const tile& t) noexcept { return t.get_value(); }

/// Get the number of worms on a tile
// Put non-alphabetically, as it depends on other functions
constexpr auto get_n_worms(const tile& t) noexcept { return get_n_worms(get_value(t)); }

/// Test the tile class
void test_tile();

std::string to_str(const tile& t);

std::ostream& operator<<(std::ostream& os, const tile& t);

#endif // TILE_H
