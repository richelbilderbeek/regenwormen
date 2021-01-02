#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "tiles.h"

/// The state of a game
class game_state
{
public:
  game_state(
    const tiles& availabe_tiles = create_all_tiles()
  );

  /// Get the tiles that are still available
  const auto& get_available_tiles() const noexcept { return m_availabe_tiles; }

private:
  /// The tiles that are still available
  tiles m_availabe_tiles;
};

/// Test the game_state class
void test_game_state();

#endif // GAME_STATE_H
