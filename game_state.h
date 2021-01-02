#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "dice_selections.h"
#include "tiles.h"

#include <iosfwd>
#include <random>

class action;

/// The state of a game
class game_state
{
public:
  /// Create a game state
  /// @param available_tiles tiles that are still available
  /// @param unavailable_tiles tiles that flipped, thus unavailable
  /// @param player_tiles collections of tiles of each player. For examples,
  ///   'player_tiles[0]' is the collection of tiles that player 1 has
  game_state(
    const tiles& available_tiles = create_all_tiles(),
    const tiles& unavailable_tiles = {},
    const std::vector<tiles> player_tiles = {{}, {}},
    const dice_selections& ds = {},
    const dice& d = {}
  );

  /// Get the tiles that are still available
  const auto& get_available_tiles() const noexcept { return m_available_tiles; }

  /// Get the zero, one or more selections of dice as already selected in the past
  const auto& get_dice_selections() const noexcept { return m_dice_selections; }

  /// Get the current dice thrown on the table
  const auto& get_dice() const noexcept { return m_dice; }

  /// Get the tiles that the players have.
  const auto& get_player_tiles() const noexcept { return m_player_tiles; }

  /// Get the tiles that are flipped, thus unavailable
  const auto& get_unavailable_tiles() const noexcept { return m_unavailable_tiles; }

  /// Roll the remaining dice on the table
  /// Throws if there are dice on the table
  void roll_dice(std::mt19937& rng_engine);

  /// 'Roll' the remaining dice on the table, making them magically land to this collection of die symbols
  /// Throws if there are dice on the table,
  /// or if the total number of dice (i.e. rolled in this function and those already selected)
  /// does not match the number of dice in the game
  void roll_dice(const dice& ds);

private:
  /// The tiles that are still available
  tiles m_available_tiles;

  /// The zero, one or more selections of dice as already selected in the past
  dice_selections m_dice_selections;

  /// The current dice thrown on the table
  dice m_dice;

  /// The tiles of each player
  std::vector<tiles> m_player_tiles;

  /// The tiles that are flipped, thus unavailable
  tiles m_unavailable_tiles;
};

/// Is it valid to do this action?
bool can_do_action(const game_state& s, const action& a);

/// Create a game state in which it only makes sense to pick a worm
game_state create_test_state_1();

/// Get the number of tiles that are still available
int get_n_available_tiles(const game_state& s);

/// Determine the number of dice that can still be thrown.
/// Will throw if dice are already on the table.
int get_n_dice_left(const game_state& s);

/// Get the number of dice currently on the table
int get_n_dice_on_table(const game_state& s) noexcept;

/// Get the number of players
int get_n_players(const game_state& s) noexcept;

/// See if there is an available tile of a certain value.
/// 'Available' means the tiles on the table, not those at the other player's stacks.
/// Use 'has_obtainable_tile_with_value' to see if a tile may be at the top
/// of other players' stacks
bool has_available_tile_with_value(const game_state& s, const int tile_value);

/// See if there is an obtainable tile of a certain value.
/// 'Obtainable' means either available, or at the top of the other player(s)' stacks
bool has_obtainable_tile_with_value(const game_state& s, const int tile_value);

/// See if there are dice currently on the table
bool has_dice_on_table(const game_state& s) noexcept;

/// Test the game_state class
void test_game_state();

/// Convert to a (multi-line string)
std::string to_str(const game_state& s) noexcept;

std::ostream& operator<<(std::ostream& os, const game_state& s) noexcept;

#endif // GAME_STATE_H
