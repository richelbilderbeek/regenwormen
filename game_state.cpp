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

game_state create_test_state_1()
{
  // Throws 6 * 3 = 18, only a 1 and worm left, while there is only a 22 available
  const tiles available_tiles = { tile(22) };
  const tiles unavailable_tiles = {};
  const std::vector<tiles> player_tiles = {{}, {}};
  const dice_selections ds = { dice_selection(die::three, 6) };
  const dice d = { die::one, die::worm };
  return game_state(
    available_tiles,
    unavailable_tiles,
    player_tiles,
    ds,
    d
  );
}

int get_n_dice_left(const game_state& s)
{
  // There must be no dice on the table, else this is confusing
  assert(get_n_dice_on_table(s) == 0);

  // Sum the number of dice in all selections
  return get_n_dice() - count_n_dice(s.get_dice_selections());
}

int get_n_dice_on_table(const game_state& s) noexcept
{
  return s.get_dice().size();
}

int get_n_available_tiles(const game_state& s)
{
  return s.get_available_tiles().size();
}

int get_n_players(const game_state& s) noexcept
{
  return s.get_player_tiles().size();
}

void game_state::roll_dice(std::mt19937& rng_engine)
{
  // Cannot roll dice if there are already dice on the table
  assert(m_dice.empty());

  const int n{get_n_dice_left(*this)};
  m_dice = create_n_random_dice(n, rng_engine);
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
    const game_state s;
    assert(get_n_players(s) == 2);
  }
  // In the initial state, all (two) players have an empty pile
  {
    const game_state s;
    assert(s.get_player_tiles().size() == 2); //Not the real test
    assert(s.get_player_tiles()[0].empty());
    assert(s.get_player_tiles()[1].empty());
  }
  // In the initial state, no dice have been selected before
  {
    const game_state s;
    assert(s.get_dice_selections().empty());
  }
  // In the initial state, no dice are on the table
  {
    const game_state s;
    assert(s.get_dice().empty());
  }
  // In the initial state, one can still roll all dice
  {
    const game_state s;
    assert(get_n_dice_left(s) == get_n_dice());
  }
  // One can roll the dice
  {
    std::mt19937 rng_engine;
    game_state g;
    assert(g.get_dice().empty());
    assert(get_n_dice_on_table(g) == 0);
    g.roll_dice(rng_engine);
    assert(!g.get_dice().empty());
    assert(get_n_dice_on_table(g) == get_n_dice());
  }
  // Create the first testing game state,
  // in which it only makes sense to pick a worm
  {
    const auto s = create_test_state_1();
    assert(get_n_dice_on_table(s) == 2);
    assert(s.get_dice()[0] == die::one);
    assert(s.get_dice()[1] == die::worm);
    assert(get_n_available_tiles(s) == 1);
    assert(get_value(s.get_available_tiles()[0]) == 22);
  }
}
