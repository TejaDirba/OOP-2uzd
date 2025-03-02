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
