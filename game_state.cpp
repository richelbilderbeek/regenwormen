#include "game_state.h"
#include "action.h"

#include <cassert>
#include <iterator>
#include <sstream>

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

bool can_do_action(const game_state& s, const action& a)
{
  // One can always give up
  if (a.get_type() == action_type::pass) return true;

  // One can roll if there are no dice on the table yet
  if (a.get_type() == action_type::roll_dice) return !has_dice_on_table(s);

  // One can select dice if that symbol is on the table
  if (a.get_type() == action_type::select_dice) return has_die_with_symbol(s.get_dice(), a.get_die());

  assert(a.get_type() == action_type::pick_tile);

  // Cannot pick a value higher than the value (no worms means zero value) of the current dice selections
  if (get_total_value(s.get_dice_selections()) < a.get_tile_value()) return false;

  // 'Obtainable' means either available, or at the top of the other player(s)' stacks
  return has_obtainable_tile_with_value(s, a.get_tile_value());
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

bool has_available_tile_with_value(const game_state& s, const int tile_value)
{
  return has_tile_with_value(s.get_available_tiles(), tile_value);
}

bool has_dice_on_table(const game_state& s) noexcept
{
  return get_n_dice_on_table(s) > 0;
}


bool has_obtainable_tile_with_value(const game_state& s, const int tile_value)
{
  // 'Obtainable' means either available, or at the top of the other player(s)' stacks
  if (has_available_tile_with_value(s, tile_value)) return true;

  // See if the other players have it...
  const int n_players{get_n_players(s)};
  assert(n_players > 1);
  for (int i = 1; i != n_players; ++i) // Start at 1, as focal player is at index 0
  {
    if (s.get_player_tiles()[i].back().get_value() == tile_value) return true;
  }
  return false;
}

void game_state::roll_dice(std::mt19937& rng_engine)
{
  // Cannot roll dice if there are already dice on the table
  assert(m_dice.empty());

  const int n{get_n_dice_left(*this)};
  m_dice = create_n_random_dice(n, rng_engine);
}

void game_state::roll_dice(const dice& ds)
{
  // Cannot roll dice if there are already dice on the table
  assert(m_dice.empty());
  assert(count_n_dice(m_dice_selections) + static_cast<int>(ds.size()) == get_n_dice());

  m_dice = ds;
}

std::string to_str(const game_state& s) noexcept
{
  using namespace std;
  std::stringstream ss;
  ss << "Dice on the table: ";
  {
    const auto& ds = s.get_dice();
    copy(begin(ds), end(ds), ostream_iterator<die>(ss, " "));
  }
  ss << '\n';
  ss << "Dice already selected: ";
  {
    const auto& ds = s.get_dice_selections();
    copy(begin(ds), end(ds), ostream_iterator<dice_selection>(ss, " "));
  }
  ss << '\n';
  ss << "Available tiles: ";
  {
    const auto& ts = s.get_available_tiles();
    copy(begin(ts), end(ts), ostream_iterator<tile>(ss, " "));
  }
  ss << '\n';
  ss << "Unavailable tiles: ";
  {
    const auto& ts = s.get_unavailable_tiles();
    copy(begin(ts), end(ts), ostream_iterator<tile>(ss, " "));
  }
  ss << '\n';
  ss << "Focal player stack: ";
  {
    const auto& ts = s.get_player_tiles()[0];
    copy(begin(ts), end(ts), ostream_iterator<tile>(ss, " "));
  }
  ss << '\n';
  assert(s.get_player_tiles().size() == 2); // For now
  ss << "Opponent stack: ";
  {
    const auto& ts = s.get_player_tiles()[1];
    copy(begin(ts), end(ts), ostream_iterator<tile>(ss, " "));
  }
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, const game_state& s) noexcept
{
  os << to_str(s);
  return os;
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
  // In the initial state, one can roll the dice
  {
    const game_state s;
    assert(can_do_action(s, create_roll_dice_action()));
  }
  // In the initial state, one can already pass, say 'your turn'
  {
    const game_state s;
    assert(can_do_action(s, create_pass_action()));
  }
  // In the initial state, before rolling the dice, one cannot select a certain die
  {
    const game_state s;
    assert(!can_do_action(s, create_select_dice_action()));
  }
  // In the initial state, before rolling the dice, one cannot pick a certain tile to take
  {
    const game_state s;
    assert(!can_do_action(s, create_pick_tile_action()));
  }
  // One can roll the dice by chance
  {
    std::mt19937 rng_engine;
    game_state g;
    assert(g.get_dice().empty());
    assert(!has_dice_on_table(g));
    assert(get_n_dice_on_table(g) == 0);
    g.roll_dice(rng_engine);
    assert(!g.get_dice().empty());
    assert(has_dice_on_table(g));
    assert(get_n_dice_on_table(g) == get_n_dice());
  }
  // One can magically roll the dice
  {
    game_state g;
    assert(g.get_dice().empty());
    assert(!has_dice_on_table(g));
    assert(get_n_dice_on_table(g) == 0);
    g.roll_dice(std::vector<die>(8, die::worm));
    assert(!g.get_dice().empty());
    assert(has_dice_on_table(g));
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
  //operator<<
  {
    const game_state s;
    std::stringstream ss;
    ss << s;
    assert(!ss.str().empty());
  }
}

