#include "game.h"
#include "tiles.h"

#include <cassert>

game::game()
  : m_tiles{create_all_tiles()}
{

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
}
