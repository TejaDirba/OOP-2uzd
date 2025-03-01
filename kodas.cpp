#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>

struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
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

// Function to read student data from a file
std::vector<Student> readStudentsFromFile(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return students;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Student student;
        ss >> student.vardas >> student.pavarde;

        int grade;
        while (ss >> grade) {
            student.nd.push_back(grade);
        }

        if (!student.nd.empty()) {
            student.egzaminas = student.nd.back();
            student.nd.pop_back(); // Last number is the exam score
        }

        student.galutinisVid = 0.4 * calculateAverage(student.nd) + 0.6 * student.egzaminas;
        student.galutinisMed = 0.4 * calculateMedian(student.nd) + 0.6 * student.egzaminas;

        students.push_back(student);
    }

    return students;
}

// Function to print results
void printResults(const std::vector<Student>& students) {
    std::cout << std::left << std::setw(15) << "Pavarde" 
              << std::setw(15) << "Vardas" 
              << std::setw(15) << "Galutinis (Vid.)"
              << std::setw(15) << "Galutinis (Med.)"
              << "\n-----------------------------------------------------------\n";

    for (const auto& student : students) {
        std::cout << std::left << std::setw(15) << student.pavarde
                  << std::setw(15) << student.vardas
                  << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisVid
                  << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisMed
                  << std::endl;
    }
}

// Comparator for sorting
bool compareByName(const Student& a, const Student& b) {
    return a.vardas < b.vardas;
}

int main() {
    std::string filename = "kursiokai.txt";
    std::vector<Student> students = readStudentsFromFile(filename);

    if (students.empty()) {
        std::cerr << "No student data found!" << std::endl;
        return 1;
    }

    int sortOption;
    std::cout << "Choose sorting method (1 - by name, 2 - by final grade average, 3 - by final grade median): ";
    std::cin >> sortOption;

    if (sortOption == 1) {
        std::sort(students.begin(), students.end(), compareByName);
    } else if (sortOption == 2) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.galutinisVid > b.galutinisVid;
        });
    } else if (sortOption == 3) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.galutinisMed > b.galutinisMed;
        });
    }

    printResults(students);
    return 0;
}
