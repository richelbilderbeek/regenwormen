#include "game_state.h"
#include "strategy.h"
#include "dice_occurances.h"
#include "game_dialog.h"
#include "ui_game_dialog.h"

#include "planned_strategy.h"
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

  // calc_p_x_same_of_n_dice
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

  // create all dice occurances and their probabilities
  ss
    << std::string(80, '-') << '\n'
    << "dice occurances (i.e. dice with the same symbol) and their probabilities:\n"
    << std::string(80, '-') << '\n'
  ;
  {
    const auto doss = create_all_dice_occurances();
    for (const auto& dos: doss)
    {
      std::string line = to_str(dos);
      // Trim to length 20
      line += std::string(20 - line.size(), ' ');
      line += std::to_string(get_probability(dos));
      ss << line << '\n';
    }
  }

  // Show all permutations
  ss
    << std::string(80, '-') << '\n'
    << "show all useful permutations:\n"
    << std::string(80, '-') << '\n'
  ;
  {
    const auto streaks = get_all_useful_permutations();
    for (const auto& ds: streaks)
    {
      ss << ds << '\n';
    }
  }

  // Show all planned_strategies (which re-shows the permutations) and their expected payoff
  ss
    << std::string(80, '-') << '\n'
    << "Show all (useful) planned strategies:\n"
    << std::string(80, '-') << '\n'
  ;
  {
    const game_state gs; // Initial game state
    const auto pss = get_all_planned_strategies();
    for (const auto& ps: pss)
    {
      std::string line = to_str(ps);
      // Trim to length 30
      line += std::string(30 - line.size(), ' ');
      line += std::to_string(calc_payoff(gs, ps));
      ss << line << '\n';
    }
  }

  // Show all payoffs per first dice symbol picked
  ss
    << std::string(80, '-') << '\n'
    << "Show all payoffs per first dice symbol picked:\n"
    << std::string(80, '-') << '\n'
  ;
  {
    const game_state gs; // Initial game state
    const auto payoffs = calc_payoff(gs);
    for (const auto& p: payoffs)
    {
      std::string line = to_str(p.first);
      // Trim to length 5
      line += std::string(5 - line.size(), ' ');
      line += std::to_string(p.second);
      ss << line << '\n';
    }
  }

  this->ui->edit->setPlainText(QString::fromStdString(ss.str()));
}
