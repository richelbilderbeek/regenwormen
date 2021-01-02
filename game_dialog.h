#ifndef GAME_DIALOG_H
#define GAME_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class game_dialog; }
QT_END_NAMESPACE

class game_state;

class game_dialog : public QDialog
{
  Q_OBJECT

public:
  game_dialog(QWidget *parent = nullptr);
  ~game_dialog();
  void show_state(const game_state& s);

private:
  Ui::game_dialog *ui;
};
#endif // GAME_DIALOG_H
