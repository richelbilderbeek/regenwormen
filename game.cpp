#include "game.h"
#include "tiles.h"

#include <cassert>

game::game()
  : m_tiles{create_all_tiles()}
{

}

bool can_get_tile(const game& g, const int value)
{
  return can_get_tile(g.get_tiles(), value);
}

void test_game()
{
  // A new game has had no turns yet
  {
    const game g;
    assert(g.get_turns().empty());
  }
  // A new game has 16 tiles
  {
    const game g;
    assert(g.get_tiles().size() == 16);
  }
  // In a new game, the tile with the lowest value is available
  {
    const game g;
    assert(can_get_tile(g, get_lowest_tile_value()));
  }
}
