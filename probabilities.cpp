#include "probabilities.h"
#include "probability.h"

#include <cassert>
#include <numeric>

// When summing the probabilities, this is approximately one
bool sum_ps_is_approx_one(const probabilities& ps)
{
  return is_approx_one(sum_probabilities(ps));
}

double sum_probabilities(const probabilities& ps)
{
  using namespace std;
  return accumulate(
    begin(ps),
    end(ps),
    0.0,
    [](const double init, const auto& p) { return init + p.second; }
  );
}

void test_probabilities()
{
  // probabilities_sum_up_to_approx_one
  {
    assert(sum_probabilities({{1, 1.0}}) == 1.0);
    assert(sum_probabilities({{1, 0.1}, {2, 0.9}}) == 1.0);
    assert(sum_probabilities({{1, 0.1}, {2, 0.2}, {3, 0.7}}) == 1.0);
    assert(sum_probabilities({{1, 0.1}, {2, 0.2}, {3, 0.3}, {4, 0.4}}) == 1.0);
  }
  // probabilities_sum_up_to_approx_one
  {
    assert(!sum_ps_is_approx_one({{1, 0.99}}));
    assert( sum_ps_is_approx_one({{1, 1.0}}));
    assert( sum_ps_is_approx_one({{1, 0.1}, {2, 0.9}}));
    assert( sum_ps_is_approx_one({{1, 0.1}, {2, 0.2}, {3, 0.7}}));
    assert( sum_ps_is_approx_one({{1, 0.1}, {2, 0.2}, {3, 0.3}, {4, 0.4}}));
  }
}
