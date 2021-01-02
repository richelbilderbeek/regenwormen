#ifndef GAME_H
#define GAME_H

#include "turns.h"

/// The 'regenwormen' game logic
class game
{
public:
  game();
  const auto& get_turns() const noexcept { return m_turns; }

private:
  turns m_turns;

};

/// Test the game class
void test_game();

#endif // GAME_H
