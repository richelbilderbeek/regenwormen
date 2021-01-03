#include "dice_occurances.h"

#include "dice.h"
#include "probability.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <sstream>

std::vector<int> calc_all_tile_values(
  const dice& ds,
  const std::vector<dice_occurances>& doss
)
{
  std::vector<int> tile_values;
  tile_values.reserve(doss.size());
  std::transform(
    std::begin(doss),
    std::end(doss),
    std::back_inserter(tile_values),
    [ds](const dice_occurances dos)
    {
      return calc_tile_value(ds, dos);
    }
  );
  return tile_values;
}

int calc_tile_value(
  const dice& ds,
  const dice_occurances& dos
)
{
  assert(has_worm(ds));
  if (dos.back() == 0) return 0;
  assert(ds.size() == dos.size());
  int tile_value = 0;
  const int n = ds.size();
  for (int i = 0; i != n; ++i)
  {
    tile_value += (get_die_value(ds[i]) * dos[i]);
  }
  return tile_value;
}

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

std::vector<dice_occurances> create_all_dice_occurances_for_n_throws(const int n)
{
  std::vector<dice_occurances> doss;
  const auto all_doss = create_all_dice_occurances();
  std::copy_if(
    std::begin(all_doss),
    std::end(all_doss),
    std::back_inserter(doss),
    [n](const auto& dos)
    {
      //Keep if
      return static_cast<int>(dos.size()) == n //it matches the number of throws
        || (static_cast<int>(dos.size()) <= n && dos.back() == 0) // the turn is ended
      ;
    }
  );
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
        // The last position can be a 0. It means zero times the desired die symbol thrown, the turn is over
        if (pos == n_digits - 1)
        {
          dos[pos] = 0;
        }
        else
        {
          dos[pos] = 1;
        }
        has_carry = true;
      }
    }
    if (sum_up_to_n_dice_at_most(dos)) break;
  }
  // Remove the first zero if it is still present
  if (dos[0] == 0) dos.erase(std::begin(dos));
  return dos;
}


std::vector<double> get_probabilities(const std::vector<dice_occurances>& doss)
{
  std::vector<double> ps;
  ps.reserve(doss.size());
  std::transform(
    std::begin(doss),
    std::end(doss),
    std::back_inserter(ps),
    [](const auto& dos){ return get_probability(dos); }
  );
  return ps;
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

bool sum_up_to_n_dice_at_most(const dice_occurances& dos)
{
  using namespace std;
  return accumulate(begin(dos), end(dos), 0) <= get_n_dice();
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
    //0,0,0,0,0,8 -> 0,0,0,0,1,0
    const dice_occurances dos = {8};
    const dice_occurances expected = {1, 0};
    const dice_occurances actual = get_next_dice_occurances(dos);
    assert(actual == expected);
  }
  {
    //0,0,0,0,1,7 -> 0,0,0,0,2,6
    const dice_occurances dos = {1, 7};
    const dice_occurances expected = {2, 0};
    const dice_occurances actual = get_next_dice_occurances(dos);
    assert(actual == expected);
  }
  {
    //0,0,0,0,7,1 -> 0,0,0,1,1,6
    const dice_occurances dos = {7, 1};
    const dice_occurances expected = {8, 0};
    const dice_occurances actual = get_next_dice_occurances(dos);
    assert(actual == expected);
  }
  // create_all_dice_occurances
  // there must be at most 8 dice rolls, but less is also fine
  {
    const auto doss = create_all_dice_occurances();
    for (const auto& dos: doss)
    {
      assert(sum_up_to_n_dice_at_most(dos));
    }
    assert(doss.size() == 460);
  }
  // One can settle on 7 dice as well and pass
  {
    const auto doss = create_all_dice_occurances();
    const dice_occurances dos = { 7 };
    assert(std::count(std::begin(doss), std::end(doss), dos) == 1);
  }
  // One can have zero times the desired die symbol
  {
    const auto doss = create_all_dice_occurances();
    const dice_occurances dos = { 0 };
    assert(std::count(std::begin(doss), std::end(doss), dos) == 1);
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
  // create_all_dice_occurances_for_n_throws
  // it may land 0, 1, 2, 3, 4, 5, 6, 7 or 8 times that die symbol
  {
    const auto dos = create_all_dice_occurances_for_n_throws(1);
    assert(dos.size() == 9);
  }
  // create_all_dice_occurances_for_n_throws
  // It may land 0, 1, 2, 3, 4, 5, 6, 7 or 8 times the first die symbol.
  // If there were zero occurances of the desired die symbol, the turn is over.
  // Else, it may land 0, 1, 2, 3, 4, 5, 6, 7 or 8 times for second die symbol,
  // if the sum is at most the number of dice
  //
  {
    const auto doss = create_all_dice_occurances_for_n_throws(2);
    const dice_occurances dos = { 0 };
    assert(
      std::count(std::begin(doss), std::end(doss), dos) == 1
    );
    assert(doss.size() == 37);
  }

}
