#include "dice_occurances.h"

#include "dice.h"

#include <algorithm>
#include <cassert>

bool sum_up_to_n_dice(const dice_occurances& dos)
{
  using namespace std;
  return accumulate(begin(dos), end(dos), 0) == get_n_dice();
}


void test_dice_occurances()
{
  // sum_up_to_n_dice
  {
    const dice_occurances dos = { 8 };
    assert(sum_up_to_n_dice(dos));
  }
}
