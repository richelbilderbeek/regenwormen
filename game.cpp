#include "game.h"
#include "tiles.h"

#include <algorithm>
#include <cassert>

game::game()
  : m_turns{},
    m_tiles{create_all_tiles()}
{

}

void game::do_turn(const turn& t)
{
  remove_tile_with_value(
    this->m_tiles,
    t.get_picked_tile_value()
  );
  m_turns.push_back(t);
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
  // After a turn in which a tile is taken, that tile is unavailable
  {
    game g;
    const auto value{get_lowest_tile_value()};
    assert(can_get_tile(g, value));
    const auto t{create_test_turn(value)};
    g.do_turn(t);
    assert(!can_get_tile(g, value));
  }
}
