#include "student.h"

int main() {
    try {
        std::string filename;
        std::cout << "Įveskite failo pavadinimą (pvz., Studentai10000.txt): ";
        std::cin >> filename;

        std::vector<Student> students = readStudentsFromFile(filename);

        if (students.empty()) {
            std::cerr << "Klaida: Nerasta studentų duomenų!" << std::endl;
            return 1;
        }

        int sortOption;
        std::cout << "Pasirinkite rūšiavimo būdą (1 - pagal vardą, 2 - pagal vidurkį, 3 - pagal medianą): ";
        std::cin >> sortOption;

        if (sortOption == 1) {
            std::sort(students.begin(), students.end(), compareByName);
        } else if (sortOption == 2) {
            std::sort(students.begin(), students.end(), compareByAvg);
        } else if (sortOption == 3) {
            std::sort(students.begin(), students.end(), compareByMedian);
        } else {
            std::cerr << "Klaida: Netinkamas pasirinkimas!" << std::endl;
            return 1;
        }

        printResults(students);
    } catch (const std::exception& e) {
        std::cerr << "Kritinė klaida: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
