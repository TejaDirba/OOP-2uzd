#include "student.h"
#include "file_operations.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;
using std::vector;
using std::string;
using std::ofstream;

void printResults(const vector<Stud>& students) {
    cout << setw(15) << "Pavarde" 
         << setw(15) << "Vardas" 
         << setw(15) << "Galutinis (Vid.)"
         << setw(15) << "Galutinis (Med.)"
         << "\n-----------------------------------------------------------\n";

    for (const auto& student : students) {
        cout << setw(15) << student.pav
             << setw(15) << student.var
             << setw(15) << fixed << setprecision(2) << student.galutinisVid
             << setw(15) << fixed << setprecision(2) << student.galutinisMed
             << endl;
    }
}

int main() {
    string filename;
    cout << "Įveskite failo pavadinimą: ";
    cin >> filename;

    vector<Stud> students = readStudentsFromFile(filename);

    if (students.empty()) {
        std::cerr << "Studentų duomenų nerasta!" << endl;
        return 1;
    }

    for (auto& student : students) {
        student.galutinisVid = 0.4 * calculateAverage(student.paz) + 0.6 * student.egz;
        student.galutinisMed = 0.4 * calculateMedian(student.paz) + 0.6 * student.egz;
    }

    int sortOption;
    cout << "Pasirinkite rikiavimo metodą (1 - pagal vardą, 2 - pagal vidurkį, 3 - pagal medianą): ";
    cin >> sortOption;

    if (sortOption == 1)
        std::sort(students.begin(), students.end(), compareByName);
    else if (sortOption == 2)
        std::sort(students.begin(), students.end(), compareByAvg);
    else if (sortOption == 3)
        std::sort(students.begin(), students.end(), compareByMedian);

    printResults(students);

    ofstream outputFile("results.txt");
    if (outputFile) {
        outputFile << setw(15) << "Pavarde" 
                   << setw(15) << "Vardas" 
                   << setw(15) << "Galutinis (Vid.)"
                   << setw(15) << "Galutinis (Med.)"
                   << "\n-----------------------------------------------------------\n";

        for (const auto& student : students) {
            outputFile << setw(15) << student.pav
                       << setw(15) << student.var
                       << setw(15) << fixed << setprecision(2) << student.galutinisVid
                       << setw(15) << fixed << setprecision(2) << student.galutinisMed
                       << endl;
        }
        cout << "Rezultatai išsaugoti į failą: results.txt" << endl;
    } else {
        std::cerr << "Klaida įrašant rezultatus į failą!" << endl;
    }

    return 0;
}
#include "student.h"
#include "file_operations.h"
#include "generator.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace chrono;

void printResults(const vector<Stud>& students) {
    cout << setw(15) << "Pavarde" 
         << setw(15) << "Vardas" 
         << setw(15) << "Galutinis (Vid.)"
         << setw(15) << "Galutinis (Med.)"
         << "\n-----------------------------------------------------------\n";

    for (const auto& student : students) {
        cout << setw(15) << student.pav
             << setw(15) << student.var
             << setw(15) << fixed << setprecision(2) << student.galutinisVid
             << setw(15) << fixed << setprecision(2) << student.galutinisMed
             << endl;
    }
}

int main() {
    string filename;
    int numStudents;

    cout << "Įveskite studentų skaičių failo generavimui: ";
    cin >> numStudents;
    filename = "students_" + to_string(numStudents) + ".txt";

    // Generate student file
    auto start = high_resolution_clock::now();
    generateStudentFile(filename, numStudents);
    auto end = high_resolution_clock::now();
    cout << "Failo generavimo laikas: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    // Read students from file
    start = high_resolution_clock::now();
    vector<Stud> students = readStudentsFromFile(filename);
    end = high_resolution_clock::now();
    cout << "Failo nuskaitymo laikas: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    if (students.empty()) {
        cerr << "Studentų duomenų nerasta!" << endl;
        return 1;
    }

    // Calculate final scores
    for (auto& student : students) {
        student.galutinisVid = 0.4 * calculateAverage(student.paz) + 0.6 * student.egz;
        student.galutinisMed = 0.4 * calculateMedian(student.paz) + 0.6 * student.egz;
    }

    // Categorize students
    vector<Stud> struggling, smart;
    for (const auto& student : students) {
        if (student.galutinisVid < 5.0)
            struggling.push_back(student);
        else
            smart.push_back(student);
    }

    // Save categorized students
    writeStudentsToFile("struggling_students.txt", struggling);
    writeStudentsToFile("smart_students.txt", smart);

    // Choose sorting method
    int sortOption;
    cout << "Pasirinkite rikiavimo metodą (1 - pagal vardą, 2 - pagal vidurkį, 3 - pagal medianą): ";
    cin >> sortOption;

    if (sortOption == 1)
        sort(students.begin(), students.end(), compareByName);
    else if (sortOption == 2)
        sort(students.begin(), students.end(), compareByAvg);
    else if (sortOption == 3)
        sort(students.begin(), students.end(), compareByMedian);

    // Print sorted results
    printResults(students);

    // Write results to file
    ofstream outputFile("results.txt");
    if (outputFile) {
        outputFile << setw(15) << "Pavarde" 
                   << setw(15) << "Vardas" 
                   << setw(15) << "Galutinis (Vid.)"
                   << setw(15) << "Galutinis (Med.)"
                   << "\n-----------------------------------------------------------\n";

        for (const auto& student : students) {
            outputFile << setw(15) << student.pav
                       << setw(15) << student.var
                       << setw(15) << fixed << setprecision(2) << student.galutinisVid
                       << setw(15) << fixed << setprecision(2) << student.galutinisMed
                       << endl;
        }
        cout << "Rezultatai išsaugoti į failą: results.txt" << endl;
    } else {
        cerr << "Klaida įrašant rezultatus į failą!" << endl;
    }

    return 0;
}

