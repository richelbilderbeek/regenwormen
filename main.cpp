#include "game_dialog.h"

#include <QApplication>

void test()
{
  assert(1 == 2);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  if (argc == 2 && std::string(argv[1]) == "--test")
  {
    test();
    return 0;
  }

  game_dialog w;
  w.show();
  return a.exec();
}
