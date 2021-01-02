#ifndef TILES_H
#define TILES_H

#include "tile.h"
#include <vector>

using tiles = std::vector<tile>;

/// Is a tile with a certain value available?
bool can_get_tile(const tiles& ts, const int value);

/// Create the 16 tiles in the game
tiles create_all_tiles() noexcept;

/// Test the tiles class
void test_tiles();

#endif // TILES_H
