#ifndef STRATEGY_H
#define STRATEGY_H

#include "action.h"
#include "game_state.h"

/// Create all actions possible
std::vector<action> create_all_actions();

/// Create all actions valid in that game state
std::vector<action> create_all_valid_actions(const game_state& s);

/// Get the best action for a certain game state
action get_best_action(const game_state& s);

/// Test this function
void test_get_best_action();

#endif // STRATEGY_H
