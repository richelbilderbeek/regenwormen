#include "dice_occurances.h"

#include "dice.h"
#include "probability.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <sstream>

std::vector<dice_occurances> create_all_dice_occurances()
{
  std::vector<dice_occurances> doss;
  auto dos = get_first_dice_occurances();
  while (1)
  {
    doss.push_back(dos);
    if (dos == get_last_dice_occurances()) break;
    dos = get_next_dice_occurances(dos);
  }
  return doss;
}

dice_occurances get_next_dice_occurances(dice_occurances dos)
{
  assert(dos.size() > 0);
  // Prepend a zero
  dos.insert(std::begin(dos), 0);
  assert(dos != get_last_dice_occurances());

  assert(dos.size() > 1);

  const int n_digits = dos.size();

  // Keep adding one, until the next valid dos is found
  while (1)
  {
    bool has_carry = true; // Start with a carry
    for (int pos = n_digits - 1 ; pos >= 0; --pos)
    {
      if (has_carry)
      {
        ++dos[pos];
        has_carry = false;
      }
      if (dos[pos] == 9)
      {
        dos[pos] = 1;
        has_carry = true;
      }
    }
    if (sum_up_to_n_dice(dos)) break;
  }
  // Remove the first zero if it is still present
  if (dos[0] == 0) dos.erase(std::begin(dos));
  return dos;
}

double get_probability(const dice_occurances dos)
{
  double p = 1.0;
  int n_dice_left = get_n_dice();
  const int n_occurances = dos.size();
  for (int pos = 0; pos != n_occurances; ++pos)
  {
    const int n_same = dos[pos];
    p *= calc_p_x_same_of_n_dice(n_same, n_dice_left);

    // Cannot re-use the dice already thrown
    n_dice_left -= n_same;
  }
   return p;
}

bool sum_up_to_n_dice(const dice_occurances& dos)
{
  using namespace std;
  return accumulate(begin(dos), end(dos), 0) == get_n_dice();
}

std::string to_str(const dice_occurances& dos)
{
  using namespace std;
  stringstream s;
  copy(begin(dos), end(dos), ostream_iterator<dice_occurance>(s, " "));
  return s.str();
}

std::ostream& operator<<(std::ostream& os, const dice_occurances& dos)
{
  os << to_str(dos);
  return os;
}

void test_dice_occurances()
{
  // sum_up_to_n_dice
  {
    assert(sum_up_to_n_dice( { 8 } ));
    assert(sum_up_to_n_dice( { 7, 1 } ));
    assert(sum_up_to_n_dice( { 6, 2 } ));
    assert(sum_up_to_n_dice( { 6, 1, 1 } ));
    assert(sum_up_to_n_dice( { 5, 3 } ));
    assert(!sum_up_to_n_dice( { 7 } ));
  }
  //get_next_dice_occurances
  {
    //0,0,0,0,0,8 -> 0,0,0,0,1,7
    const dice_occurances dos = {8};
    const dice_occurances expected = {1, 7};
    const dice_occurances actual = get_next_dice_occurances(dos);
    assert(actual == expected);
  }
  {
    //0,0,0,0,1,7 -> 0,0,0,0,2,6
    const dice_occurances dos = {1, 7};
    const dice_occurances expected = {2, 6};
    const dice_occurances actual = get_next_dice_occurances(dos);
    assert(actual == expected);
  }
  {
    //0,0,0,0,7,1 -> 0,0,0,1,1,6
    const dice_occurances dos = {7, 1};
    const dice_occurances expected = {1, 1, 6};
    const dice_occurances actual = get_next_dice_occurances(dos);
    assert(actual == expected);
  }
  // create_all_dice_occurances
  {
    const auto doss = create_all_dice_occurances();
    for (const auto& dos: doss)
    {
      assert(sum_up_to_n_dice(dos));
    }
    assert(doss.size() == 120);
  }
  // get_probability
  {
    const dice_occurances dos = { 8 };
    const auto expected = int_pow(1.0 / 6.0, 8);
    const auto actual = get_probability(dos);
    assert(actual == expected);
  }
  // get_probability
  {
    const dice_occurances dos = { 3, 1, 1, 1, 1, 1 };
    const auto expected{
        calc_p_x_same_of_n_dice(3, 8)
      * calc_p_x_same_of_n_dice(1, 5)
      * calc_p_x_same_of_n_dice(1, 4)
      * calc_p_x_same_of_n_dice(1, 3)
      * calc_p_x_same_of_n_dice(1, 2)
      * calc_p_x_same_of_n_dice(1, 1)
    };
    const auto actual = get_probability(dos);
    assert(actual == expected);
  }

}
