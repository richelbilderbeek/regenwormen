#ifndef PROBABILITY_H
#define PROBABILITY_H


// Adapted from https://github.com/kthohr/gcem/blob/master/include/gcem_incl/binomial_coef.hpp#L30
constexpr int binomial_coefficient(const int n, const int k) noexcept
{
  return
   (k == 0 || n == k) ? 1 : // deals with 0 choose 0 case
   n == 0 ? 0 :
   binomial_coefficient(n - 1, k - 1) + binomial_coefficient(n - 1, k);
}

// From https://solarianprogrammer.com/2017/12/27/cpp-17-constexpr-everything-as-much-as-the-compiler-can/
constexpr int factorial(int n) {
  return n <= 1 ? 1 : (n * factorial(n - 1));
}

/// Calculate p to the power of n
// Adapted from http://prosepoetrycode.potterpcs.net/2015/07/a-simple-constexpr-power-function-c/
constexpr double int_pow(double p, unsigned int n)
{
  return (n >= sizeof(unsigned int) * 8) ? 0 :
    n == 0 ? 1 : p * int_pow(p, n - 1)
  ;
}

/// Determine if the number if approximately 1.0
constexpr bool is_approx_one(double x)
{
  return x > 0.999999999 && x < 1.000000001;
}

/// Determine if the number if approximately 1.0
constexpr bool x_is_approx_y(double x, double y)
{
  return x - y > -0.000000001 && x - y < 0.000000001;
}

/// Calculate the expected probability
/// to have x times the same symbol when
/// throwing n dice
constexpr double calc_p_x_same_of_n_dice(const int x, const int n)
{
  return int_pow(1.0 / 6.0, x) * int_pow(5.0 / 6.0, n - x) * binomial_coefficient(n, x);
}

void test_probability();

#endif // PROBABILITY_H
