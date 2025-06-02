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

std::vector<Student> readStudentsFromFile(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return students;
    }

    std::string line;
    std::getline(file, line);  // skipping the header

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
            student.nd.pop_back();  // remove the last element used as the exam score
        }

        student.galutinisVid = 0.4 * calculateAverage(student.nd) + 0.6 * student.egzaminas;
        student.galutinisMed = 0.4 * calculateMedian(student.nd) + 0.6 * student.egzaminas;

        students.push_back(student);
    }

    return students;
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


bool compareByName(const Student& a, const Student& b) {
    return a.vardas < b.vardas;
}

bool compareByAvg(const Student& a, const Student& b) {
    return a.galutinisVid > b.galutinisVid;
}

bool compareByMedian(const Student& a, const Student& b) {
    return a.galutinisMed > b.galutinisMed;
}

int main() {
    std::string filename;
    std::cout << "Enter the file name (e.g., Studentai10000.txt): ";
    std::cin >> filename;

    std::vector<Student> students = readStudentsFromFile(filename);

    if (students.empty()) {
        std::cerr << "No student data found!" << std::endl;
        return 1;
    }

    int sortOption;
    std::cout << "Pasirinkite rūšiavimą (1-Vardas, 2-Vidurkis, 3-Mediana): ";
    std::cin >> sortOption;

    if (sortOption == 1) {
        std::sort(students.begin(), students.end(), compareByName);
    } else if (sortOption == 2) {
        std::sort(students.begin(), students.end(), compareByAvg);
    } else if (sortOption == 3) {
        std::sort(students.begin(), students.end(), compareByMedian);
    }

    std::ofstream outputFile("results.txt");
    if (outputFile) {
        outputFile << std::left << std::setw(15) << "Pavarde" 
                   << std::setw(15) << "Vardas" 
                   << std::setw(15) << "Galutinis (Vid.)"
                   << std::setw(15) << "Galutinis (Med.)"
                   << "\n-----------------------------------------------------------\n";

        for (const auto& student : students) {
            outputFile << std::left << std::setw(15) << student.pavarde
                       << std::setw(15) << student.vardas
                       << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisVid
                       << std::setw(15) << std::fixed << std::setprecision(2) << student.galutinisMed
                       << std::endl;
        }
        outputFile.close();
        std::cout << "Results saved to: results.txt" << std::endl;
    } else {
        std::cerr << "Error writing results to file!" << std::endl;
    }

    return 0;
}
