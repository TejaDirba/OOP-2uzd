#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>

class Student {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;

public:
    Student();
    Student(const std::string& v, const std::string& p);

    // Rule of Five
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;
    ~Student();

    std::string getVardas() const;
    std::string getPavarde() const;
    std::vector<int> getNd() const;
    int getEgzaminas() const;
    double getGalutinisVid() const;
    double getGalutinisMed() const;

    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);
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
double calculateAverage(const std::vector<int>& v);
double calculateMedian(std::vector<int> v);

#endif // STUDENT_H
