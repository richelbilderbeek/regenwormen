#ifndef DICE_SELECTION_H
#define DICE_SELECTION_H

#include "dice.h"

/// A selected collection of dice, a roll.
/// Each dice roll has one or more dice of the same value
class dice_selection
{
public:
  /// Create a dice_selection, which is one or more dice of the same value
  /// @param d the symbol on the dice
  /// @param n the number of dice
  constexpr dice_selection(
    const die d,
    const int n
  ) : m_die{d}, m_n{n}
  {


  }

  /// The number of dice
  constexpr int get_size() const noexcept { return m_n; }

  /// The symbol on the dice
  constexpr die get_die() const noexcept { return m_die; }

  private:
  die m_die;
  int m_n;
};

dice_selection create_test_dice_selection(const die d = die::one, const int n = 1);

/// Get the symbol/value of a dice selection
constexpr die get_die(const dice_selection& r) noexcept { return r.get_die(); }

/// Get the number of dice in a selection
constexpr int get_size(const dice_selection& r) noexcept { return r.get_size(); }

/// Get the value of the symbol in the selection
constexpr int get_die_value(const dice_selection& r) noexcept { return get_die_value(get_die(r)); }

/// Get the summed value of the selection
// Not at the alphabetic position, as it depends on two other functions
constexpr int get_summed_value(const dice_selection& r) noexcept
{
  return get_die_value(r) * get_size(r);
}


/// Does this dice roll has worms?
constexpr bool has_worms(const dice_selection& r) noexcept { return get_die(r) == die::worm; }

/// Test the DICE_SELECTION class
void test_dice_selection();

std::string to_str(const dice_selection& ds);

std::ostream& operator<<(std::ostream& os, const dice_selection& ds);

#endif // DICE_SELECTION_H
