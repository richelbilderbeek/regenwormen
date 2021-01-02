#include "game_state.h"

#include <cassert>

game_state::game_state(
  const tiles& availabe_tiles
) : m_availabe_tiles{availabe_tiles}
{

}

void test_game_state()
{
  // A state has a collection of tiles that are available
  {
    game_state g;
    assert(!g.get_available_tiles().empty());
  }
}
