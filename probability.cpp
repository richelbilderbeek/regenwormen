#include "probability.h"

void test_probability()
{
  static_assert(factorial(1) == 1);
  static_assert(factorial(2) == 2);
  static_assert(factorial(3) == 6);
  static_assert(factorial(4) == 24);
  static_assert(factorial(5) == 120);
  static_assert(factorial(6) == 720);
  static_assert(factorial(7) == 720 * 7);
  static_assert(factorial(8) == 720 * 7 * 8);
  static_assert(int_pow(0.5, 0) == 1.0);
  static_assert(int_pow(0.5, 1) == 0.5);
  static_assert(int_pow(0.5, 2) == 0.25);
  static_assert(int_pow(0.5, 3) == 0.125);
  static_assert(binomial_coefficient(0, 0) == 1);
  static_assert(binomial_coefficient(0, 1) == 0);
  static_assert(binomial_coefficient(0, 2) == 0);
  static_assert(binomial_coefficient(0, 3) == 0);
  static_assert(binomial_coefficient(2, 0) == 1);
  static_assert(binomial_coefficient(2, 1) == 2);
  static_assert(binomial_coefficient(2, 2) == 1);
  static_assert(binomial_coefficient(3, 0) == 1);
  static_assert(binomial_coefficient(3, 1) == 3);
  static_assert(binomial_coefficient(3, 2) == 3);
  static_assert(binomial_coefficient(3, 3) == 1);
  static_assert(binomial_coefficient(4, 0) == 1);
  static_assert(binomial_coefficient(4, 1) == 4);
  static_assert(binomial_coefficient(4, 2) == 6);
  static_assert(binomial_coefficient(4, 3) == 4);
  static_assert(binomial_coefficient(4, 4) == 1);
  static_assert(binomial_coefficient(5, 0) == 1);
  static_assert(binomial_coefficient(5, 1) == 5);
  static_assert(binomial_coefficient(5, 2) == 10);
  static_assert(binomial_coefficient(5, 3) == 10);
  static_assert(binomial_coefficient(5, 4) == 5);
  static_assert(binomial_coefficient(5, 5) == 1);

  //                                                           +--- focal symbol occurence
  //                                                           |
  //                                                           |                       +--- other symbol occurrance
  //                                                           |                       |
  //                                                           |                       |    +--- number of combinations
  //                                                           |                       |    |
  //                                                           V                       V    V
  static_assert(calc_p_x_same_of_n_dice(0, 1) == int_pow(1.0 / 6.0, 0) * int_pow(5.0 / 6.0, 1) * 1);
  static_assert(calc_p_x_same_of_n_dice(1, 1) == int_pow(1.0 / 6.0, 1) * int_pow(5.0 / 6.0, 0) * 1);

  static_assert(calc_p_x_same_of_n_dice(0, 2) == int_pow(1.0 / 6.0, 0) * int_pow(5.0 / 6.0, 2) * 1);
  static_assert(calc_p_x_same_of_n_dice(1, 2) == int_pow(1.0 / 6.0, 1) * int_pow(5.0 / 6.0, 1) * 2);
  static_assert(calc_p_x_same_of_n_dice(2, 2) == int_pow(1.0 / 6.0, 2) * int_pow(5.0 / 6.0, 0) * 1);

  static_assert(calc_p_x_same_of_n_dice(0, 3) == int_pow(1.0 / 6.0, 0) * int_pow(5.0 / 6.0, 3) * 1);
  static_assert(calc_p_x_same_of_n_dice(1, 3) == int_pow(1.0 / 6.0, 1) * int_pow(5.0 / 6.0, 2) * 3);
  static_assert(calc_p_x_same_of_n_dice(2, 3) == int_pow(1.0 / 6.0, 2) * int_pow(5.0 / 6.0, 1) * 3);
  static_assert(calc_p_x_same_of_n_dice(3, 3) == int_pow(1.0 / 6.0, 3) * int_pow(5.0 / 6.0, 0) * 1);

  static_assert(calc_p_x_same_of_n_dice(0, 4) == int_pow(1.0 / 6.0, 0) * int_pow(5.0 / 6.0, 4) * 1);
  static_assert(calc_p_x_same_of_n_dice(1, 4) == int_pow(1.0 / 6.0, 1) * int_pow(5.0 / 6.0, 3) * 4);
  static_assert(calc_p_x_same_of_n_dice(2, 4) == int_pow(1.0 / 6.0, 2) * int_pow(5.0 / 6.0, 2) * 6);
  static_assert(calc_p_x_same_of_n_dice(3, 4) == int_pow(1.0 / 6.0, 3) * int_pow(5.0 / 6.0, 1) * 4);
  static_assert(calc_p_x_same_of_n_dice(4, 4) == int_pow(1.0 / 6.0, 4) * int_pow(5.0 / 6.0, 0) * 1);

  static_assert(!is_approx_one(0.999));
  static_assert( is_approx_one(1.000));
  static_assert(!is_approx_one(1.001));

  static_assert(!x_is_approx_y(0.999, 1.0));
  static_assert( x_is_approx_y(1.000, 1.0));
  static_assert(!x_is_approx_y(1.001, 1.0));

  static_assert(!x_is_approx_y( 99.999, 100.0));
  static_assert( x_is_approx_y(100.000, 100.0));
  static_assert(!x_is_approx_y(100.001, 100.0));

  // Sum of probabilities must be 1.0
  static_assert(calc_p_x_same_of_n_dice(0, 1) + calc_p_x_same_of_n_dice(1, 1) == 1.0);
  static_assert(
      calc_p_x_same_of_n_dice(0, 2)
    + calc_p_x_same_of_n_dice(1, 2)
    + calc_p_x_same_of_n_dice(2, 2)
   == 1.0
  );
  static_assert(
      calc_p_x_same_of_n_dice(0, 3)
    + calc_p_x_same_of_n_dice(1, 3)
    + calc_p_x_same_of_n_dice(2, 3)
    + calc_p_x_same_of_n_dice(3, 3)
   == 1.0
  );
  // Loss of numeric precisio
  static_assert(
    is_approx_one(
        calc_p_x_same_of_n_dice(0, 4)
      + calc_p_x_same_of_n_dice(1, 4)
      + calc_p_x_same_of_n_dice(2, 4)
      + calc_p_x_same_of_n_dice(3, 4)
      + calc_p_x_same_of_n_dice(4, 4)
    )
  );
  static_assert(
    is_approx_one(
        calc_p_x_same_of_n_dice(0, 5)
      + calc_p_x_same_of_n_dice(1, 5)
      + calc_p_x_same_of_n_dice(2, 5)
      + calc_p_x_same_of_n_dice(3, 5)
      + calc_p_x_same_of_n_dice(4, 5)
      + calc_p_x_same_of_n_dice(5, 5)
    )
  );
  static_assert(
    is_approx_one(
        calc_p_x_same_of_n_dice(0, 6)
      + calc_p_x_same_of_n_dice(1, 6)
      + calc_p_x_same_of_n_dice(2, 6)
      + calc_p_x_same_of_n_dice(3, 6)
      + calc_p_x_same_of_n_dice(4, 6)
      + calc_p_x_same_of_n_dice(5, 6)
      + calc_p_x_same_of_n_dice(6, 6)
    )
  );
  static_assert(
    is_approx_one(
        calc_p_x_same_of_n_dice(0, 7)
      + calc_p_x_same_of_n_dice(1, 7)
      + calc_p_x_same_of_n_dice(2, 7)
      + calc_p_x_same_of_n_dice(3, 7)
      + calc_p_x_same_of_n_dice(4, 7)
      + calc_p_x_same_of_n_dice(5, 7)
      + calc_p_x_same_of_n_dice(6, 7)
      + calc_p_x_same_of_n_dice(7, 7)
    )
  );
  static_assert(
    is_approx_one(
        calc_p_x_same_of_n_dice(0, 8)
      + calc_p_x_same_of_n_dice(1, 8)
      + calc_p_x_same_of_n_dice(2, 8)
      + calc_p_x_same_of_n_dice(3, 8)
      + calc_p_x_same_of_n_dice(4, 8)
      + calc_p_x_same_of_n_dice(5, 8)
      + calc_p_x_same_of_n_dice(6, 8)
      + calc_p_x_same_of_n_dice(7, 8)
      + calc_p_x_same_of_n_dice(8, 8)
    )
  );

}
