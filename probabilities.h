#ifndef PROBABILITIES_H
#define PROBABILITIES_H

#include <map>

/// The probabilities to have a specific tile value
using probabilities = std::map<int, double>;

/// See if the probabilities sum up to approximately one
bool sum_ps_is_approx_one(const probabilities& p);

/// Get the sum of all probabilities
double sum_probabilities(const probabilities& p);

/// Test the probabilities class
void test_probabilities();

#endif // PROBABILITIES_H
