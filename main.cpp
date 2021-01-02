#include "action.h"
#include "dice_selection.h"
#include "dice_selections.h"
#include "game.h"
#include "game_state.h"
#include "tiles.h"
#include "turn.h"
#include "strategy.h"
#include "game_dialog.h"

#include <iostream>
#include <QApplication>

void test()
{
  // Order should be more-or-less in increasing complexity, so that
  // the root cause of an error can be found more easily
  test_die();
  test_dice();
  test_tile();
  test_tiles();
  test_dice_selection();
  test_dice_selections();
  test_turn();
  test_game_state();
  test_game();
  test_action_type();
  test_action();
  test_get_best_action();
}

int main(int argc, char *argv[])
{
  #ifndef NDEBUG
  std::cout << "Debug mode\n";
  test();
  #else
  std::cout << "Release mode\n";
  assert(1 == 2); //No tests in release mode
  #endif

  if (argc == 2 && std::string(argv[1]) == "--test") return 0;

  QApplication a(argc, argv);
  game_dialog w;
  w.show();
  return a.exec();
}
