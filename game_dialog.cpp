#include "game_state.h"
#include "strategy.h"

#include "game_dialog.h"
#include "ui_game_dialog.h"

#include <sstream>

game_dialog::game_dialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::game_dialog)
{
  ui->setupUi(this);
  const game_state s;
  show_state(s);
}

game_dialog::~game_dialog()
{
  delete ui;
}

void game_dialog::show_state(const game_state& s)
{
  using namespace std;

  // Show the state
  {
    stringstream ss;
    ss << s;
    this->ui->edit_state->setPlainText(QString::fromStdString(ss.str()));

  }
  // Show the actions
  {
    const auto as = create_all_valid_actions(s);
    stringstream ss;
    copy(begin(as), end(as), ostream_iterator<action>(ss, "\n"));
    this->ui->edit_actions->setPlainText(QString::fromStdString(ss.str()));
  }
}
