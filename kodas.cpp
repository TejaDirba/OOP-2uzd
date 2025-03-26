#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>

struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
};

double calculateAverage(const std::vector<int>& nd) {
    if (nd.empty()) return 0;
    return std::accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
}

double calculateMedian(std::vector<int> nd) {
    if (nd.empty()) return 0;
    std::sort(nd.begin(), nd.end());
    size_t size = nd.size();
    if (size % 2 == 0) 
        return (nd[size / 2 - 1] + nd[size / 2]) / 2.0;
    else 
        return nd[size / 2];
}

// Fdinaminis input perskaitymas
void inputStudents(std::vector<Student>& students) {
    int studentCount;
    std::cout << "Įveskite studentų skaičių: ";
    std::cin >> studentCount;

    for (int i = 0; i < studentCount; i++) {
        Student student;
        std::cout << "Vardas ir pavardė: ";
        std::cin >> student.vardas >> student.pavarde;

        std::vector<int> homeworkScores;
        int homework;
        std::cout << "Suveskite namų darbų pažymius (-1 to finish): ";
        while (true) {
            std::cin >> homework;
            if (homework == -1) break;
            homeworkScores.push_back(homework);
        }

        std::cout << "Suveskite egzamino pažymį: ";
        std::cin >> student.egzaminas;

        student.nd = homeworkScores;
        student.galutinisVid = 0.4 * calculateAverage(student.nd) + 0.6 * student.egzaminas;
        student.galutinisMed = 0.4 * calculateMedian(student.nd) + 0.6 * student.egzaminas;

        students.push_back(student);
    }
}

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
    std::vector<Student> students;
    inputStudents(students);

    if (students.empty()) {
        std::cerr << "Nesuvesti studento duomenys!" << std::endl;
        return 1;
    }

    int sortOption;
    std::cout << "Pasirinkite pagal ką norite rušiuoti (1 - Vardu, 2 - Vidurkiu, 3 - Mediana): ";
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

