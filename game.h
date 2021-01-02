#ifndef GAME_H
#define GAME_H

#include "tiles.h"
#include "turns.h"

/// The 'regenwormen' game logic
class game
{
public:
  game();
  const auto& get_turns() const noexcept { return m_turns; }
  const auto& get_tiles() const noexcept { return m_tiles; }

private:
  turns m_turns;
  tiles m_tiles;
};

/// Is a tile with a specific value still available?
bool can_get_tile(const game& g, const int value);

/// Test the game class
void test_game();

#endif // GAME_H
