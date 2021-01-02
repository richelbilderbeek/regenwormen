#include "game_state.h"

#include <cassert>

game_state::game_state(
  const tiles& available_tiles,
  const tiles& unavailable_tiles,
  const std::vector<tiles> player_tiles
) : m_available_tiles{available_tiles},
    m_player_tiles{player_tiles},
    m_unavailable_tiles{unavailable_tiles}
{

}

int get_n_players(const game_state& s) noexcept
{
  return s.get_player_tiles().size();
}

void test_game_state()
{
  // A state has a collection of tiles that are available
  {
    game_state g;
    assert(!g.get_available_tiles().empty());
    assert(g.get_unavailable_tiles().empty());
  }
  // A state has two players by defau;t
  {
    game_state g;
    assert(get_n_players(g) == 2);
  }
}
