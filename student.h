#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::sort;
using std::accumulate;

struct Stud {
    string var = "a", pav = "a";
    vector<int> paz;
    int egz = 9;
    double galutinisVid = 0.0, galutinisMed = 0.0;
};

double calculateAverage(const vector<int>& paz);
double calculateMedian(vector<int> paz);
vector<Stud> readStudentsFromFile(const string& filename);
void printResults(const vector<Stud>& students);
bool compareByName(const Stud& a, const Stud& b);
bool compareByAvg(const Stud& a, const Stud& b);
bool compareByMedian(const Stud& a, const Stud& b);

#endif
