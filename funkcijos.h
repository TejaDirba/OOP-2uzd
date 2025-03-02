#ifndef UTILS_H
#define UTILS_H

#include "student.h"
#include <algorithm>
#include <numeric>

double calculateAverage(const vector<int>& paz);
double calculateMedian(vector<int> paz);
bool compareByName(const Stud& a, const Stud& b);
bool compareByAvg(const Stud& a, const Stud& b);
bool compareByMedian(const Stud& a, const Stud& b);

#endif // UTILS_H
