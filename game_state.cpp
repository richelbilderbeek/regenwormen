#include "game_state.h"

#include <cassert>

game_state::game_state(
  const tiles& available_tiles,
  const tiles& unavailable_tiles,
  const std::vector<tiles> player_tiles,
  const dice_selections& ds,
  const dice& d
) : m_available_tiles{available_tiles},
    m_dice_selections{ds},
    m_dice{d},
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
  // The initial state has all tiles available
  {
    const game_state g;
    assert(g.get_available_tiles().size() == create_all_tiles().size());
  }
  // The initial state has no unavailable tiles
  {
    const game_state g;
    assert(g.get_unavailable_tiles().empty());
  }
  // A state has two players by default
  {
    const game_state g;
    assert(get_n_players(g) == 2);
  }
  // In the initial state, all (two) players have an empty pile
  {
    const game_state g;
    assert(g.get_player_tiles().size() == 2); //Not the real test
    assert(g.get_player_tiles()[0].empty());
    assert(g.get_player_tiles()[1].empty());
  }
  // In the initial state, no dice have been selected before
  {
    const game_state g;
    assert(g.get_dice_selections().empty());
  }
  // In the initial state, no dice are on the table
  {
    const game_state g;
    assert(g.get_dice().empty());
  }
}
