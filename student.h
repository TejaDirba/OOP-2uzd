#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

struct Stud {
    string var = "a", pav = "a";
    vector<int> paz;
    int egz = 9;
    double galutinisVid = 0.0, galutinisMed = 0.0;
};

#endif // STUDENT_H
