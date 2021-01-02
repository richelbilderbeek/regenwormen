#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "tiles.h"

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
    const std::vector<tiles> player_tiles = {{}, {}}
  );

  /// Get the tiles that are still available
  const auto& get_available_tiles() const noexcept { return m_available_tiles; }

  /// Get the tiles that the players have.
  const auto& get_player_tiles() const noexcept { return m_player_tiles; }

  /// Get the tiles that are flipped, thus unavailable
  const auto& get_unavailable_tiles() const noexcept { return m_unavailable_tiles; }

private:
  /// The tiles that are still available
  tiles m_available_tiles;

  /// The tiles of each player
  std::vector<tiles> m_player_tiles;

  /// The tiles that are flipped, thus unavailable
  tiles m_unavailable_tiles;
};

/// Get the number of players
int get_n_players(const game_state& s) noexcept;

/// Test the game_state class
void test_game_state();

#endif // GAME_STATE_H
