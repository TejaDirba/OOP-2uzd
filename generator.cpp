#include "generator.h"
#include "student.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Function to generate a random integer within a range
int getRandomNumber(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// Function to generate a random student name
string generateRandomName(bool isFirstName) {
    vector<string> firstNames = {"Jonas", "Petras", "Ona", "Ieva", "Tomas", "Lukas", "Milda", "Aiste", "Rokas", "Greta"};
    vector<string> lastNames = {"Kazlauskas", "Petrauskas", "Jankauskas", "Vilkas", "Šaltis", "Stankevičius", "Žemaitis", "Kavaliauskas"};

    if (isFirstName) {
        return firstNames[getRandomNumber(0, firstNames.size() - 1)];
    } else {
        return lastNames[getRandomNumber(0, lastNames.size() - 1)];
    }
}

// Function to generate a student data file
void generateStudentFile(const string& filename, int studentCount) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Klaida kuriant failą: " << filename << endl;
        return;
    }

    outFile << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 Egzaminas\n";  // Header row

    for (int i = 0; i < studentCount; ++i) {
        string lastName = generateRandomName(false);
        string firstName = generateRandomName(true);
        outFile << lastName << " " << firstName;

        // Generate 5 random homework grades and final exam score
        for (int j = 0; j < 5; ++j) {
            outFile << " " << getRandomNumber(1, 10);
        }
        outFile << " " << getRandomNumber(1, 10) << "\n";
    }

    outFile.close();
    cout << "Sukurta " << studentCount << " studentų duomenų į failą: " << filename << endl;
}
