#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Student.h"
#include <vector>
#include <list>
#include <deque>
#include <string>

class FileManager {
public:
    static std::vector<Student> readStudentsFromFile(const std::string& filename);
    static void writeResultsToFile(const std::vector<Student>& students,const std::string& filename="results.txt");
    static void printHeader();
    static void printResults(const std::vector<Student>& students);
    static void splitAndWriteVector(const std::vector<Student>& all,const std::string& base);
    static void splitAndWriteList(const std::list<Student>& all,const std::string& base);
    static void splitAndWriteDeque(const std::deque<Student>& all,const std::string& base);
    template<typename C> static void readIntoContainer(const std::string& filename,C& out);
    static void splitStrategy1_Vector(const std::vector<Student>& data,std::vector<Student>& fail,std::vector<Student>& pass);
    static void splitStrategy2_Vector(std::vector<Student>& data,std::vector<Student>& fail);
    static void splitStrategy1_List(const std::list<Student>& data,std::list<Student>& fail,std::list<Student>& pass);
    static void splitStrategy2_List(std::list<Student>& data,std::list<Student>& fail);
    static void splitStrategy1_Deque(const std::deque<Student>& data,std::deque<Student>& fail,std::deque<Student>& pass);
    static void splitStrategy2_Deque(std::deque<Student>& data,std::deque<Student>& fail);
    static void generateTestFiles();
private:
    static void parseStudentLine(const std::string& line,Student& s);
    static bool isValidGrade(int g);
};

#endif
