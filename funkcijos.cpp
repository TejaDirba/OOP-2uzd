#include "file_operations.h"

vector<Stud> readStudentsFromFile(const string& filename) {
    vector<Stud> students;
    ifstream file(filename);

    if (!file) {
        std::cerr << "Klaida atidarant failą: " << filename << std::endl;
        return students;
    }

    string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        stringstream ss(line);
        Stud student;
        ss >> student.var >> student.pav;
        int grade;
        while (ss >> grade) {
            student.paz.push_back(grade);
        }
        if (!student.paz.empty()) {
            student.egz = student.paz.back();
            student.paz.pop_back();
        }
        students.push_back(student);
    }
    return students;
}
