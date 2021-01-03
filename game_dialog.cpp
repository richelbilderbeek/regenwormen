#include "game_state.h"
#include "strategy.h"

#include "game_dialog.h"
#include "ui_game_dialog.h"

#include "probability.h"

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
  stringstream ss;
  ss
    << std::string(80, '-') << '\n'
    << "State:\n"
    << std::string(80, '-') << '\n'
    << s
    << "\n\n"
  ;

  // Show the actions
  const auto as = create_all_valid_actions(s);
  ss
    << std::string(80, '-') << '\n'
    << "Actions:\n"
    << std::string(80, '-') << '\n'
  ;
  copy(begin(as), end(as), ostream_iterator<action>(ss, "\n"));
  ss << "\n\n";

  ss
    << std::string(80, '-') << '\n'
    << "calc_p_x_same_of_n_dice, chance to have x the same from n dice:\n"
    << std::string(80, '-') << '\n'
  ;
  for (int n_dice = 1; n_dice != 9; ++n_dice)
  {
    for (int n_same = 0; n_same != n_dice + 1; ++n_same)
    {
      ss << "p(n_same = " << n_same << ", n_dice = " << n_dice << ") = " << calc_p_x_same_of_n_dice(n_same, n_dice) << '\n';
    }
    ss << '\n';
  }



  this->ui->edit->setPlainText(QString::fromStdString(ss.str()));

}
