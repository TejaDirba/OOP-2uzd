#ifndef STUDENT_H
#define STUDENT_H

#include "Zmogus.h"
#include <vector>
#include <iostream>

class Student : public Zmogus {
private:
    std::vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;

public:
    Student();
    Student(const std::string& v, const std::string& p);
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;
    ~Student() override;

    std::vector<int> getNd() const;
    int getEgzaminas() const;
    double getGalutinisVid() const;
    double getGalutinisMed() const;

    void setNd(const std::vector<int>& grades);
    void setEgzaminas(int e);
    void addHomeworkGrade(int grade);
    void calculateFinalGrades();

    friend std::istream& operator>>(std::istream& is, Student& s);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

bool compareByName(const Student& a, const Student& b);
bool compareByAvg(const Student& a, const Student& b);
bool compareByMedian(const Student& a, const Student& b);

#endif
