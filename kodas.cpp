#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>

// Structure to hold student data
struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;  // Homeworks using a vector
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
};

// Function to calculate the average
double calculateAverage(const std::vector<int>& nd) {
    if (nd.empty()) return 0;
    return std::accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
}

// Function to calculate the median
double calculateMedian(std::vector<int> nd) {
    if (nd.empty()) return 0;
    std::sort(nd.begin(), nd.end());
    size_t size = nd.size();
    if (size % 2 == 0) 
        return (nd[size / 2 - 1] + nd[size / 2]) / 2.0;
    else 
        return nd[size / 2];
}

// Function to read student data from **user input** dynamically
void inputStudents(std::vector<Student>& students) {
    int studentCount;
    std::cout << "Enter the number of students: ";
    std::cin >> studentCount;

    for (int i = 0; i < studentCount; i++) {
        Student student;
        std::cout << "Enter student's first name and last name: ";
        std::cin >> student.vardas >> student.pavarde;

        std::vector<int> homeworkScores;
        int
