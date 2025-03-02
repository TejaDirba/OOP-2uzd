#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "student.h"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::stringstream;
using std::vector;
using std::string;

vector<Stud> readStudentsFromFile(const string& filename);

#endif // FILE_OPERATIONS_H
