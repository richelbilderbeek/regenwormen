#ifndef PROBABILITIES_H
#define PROBABILITIES_H

#include <map>

/// The probabilities to have a specific tile value
using probabilities = std::map<int, double>;

/// See if the probabilities sum up to approximately one
bool probabilities_sum_up_to_approx_one(const probabilities& p);

/// Test the probabilities class
void test_probabilities();

#endif // PROBABILITIES_H
