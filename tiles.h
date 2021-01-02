#ifndef TILES_H
#define TILES_H

#include "tile.h"
#include <vector>

using tiles = std::vector<tile>;

/// Create the 16 tiles in the game
tiles create_all_tiles() noexcept;

/// Test the tiles class
void test_tiles();

#endif // TILES_H
