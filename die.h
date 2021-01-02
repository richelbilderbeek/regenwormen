#ifndef DIE_H
#define DIE_H

/// One 'regenwormen' die.
/// Use the 'dice' class for a collection of dice.
enum class die
{
  one, two, three, four, five, worm
};

/// Get a die with the correct value
/// Will return die::five for a value of 5
die get_die_with_value(const int value);

/// The minimum value a dice can have.
constexpr int get_min_dice_value() noexcept { return 1; }

/// The maximum value a dice can have.
/// Because a worm also has a value of 5 (instead of the expected 6),
/// this value is 5
constexpr int get_max_dice_value() noexcept { return 5; }

/// Get the value of the die,
/// which equals the number of eyes,
/// and a value of 5 for the worm
constexpr int get_die_value(const die d) noexcept
{
  switch (d)
  {
    case die::one: return 1;
    case die::two: return 2;
    case die::three: return 3;
    case die::four: return 4;
    case die::five: return 5;
    case die::worm:
    default: return 5;
  }
}

/// Test the die class
void test_die();

#endif // DIE_H
