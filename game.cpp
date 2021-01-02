#include "game.h"
#include <cassert>

game::game()
{

}

void test_game()
{
  // A new game has had no turns yet
  {
    const game g;
    assert(g.get_turns().empty());
  }
}
