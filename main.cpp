#include "game.h"
#include "tiles.h"

#include "game_dialog.h"

#include <iostream>
#include <QApplication>

void test()
{
  test_tile();
  test_tiles();
  test_game();
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
