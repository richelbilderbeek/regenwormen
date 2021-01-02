#ifndef STRATEGY_H
#define STRATEGY_H

#include "action.h"
#include "game_state.h"

/// Get the best action for a certain game state
action get_best_action(const game_state& s);

/// Test this function
void test_get_best_action();

#endif // STRATEGY_H
