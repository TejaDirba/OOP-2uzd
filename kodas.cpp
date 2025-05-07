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


void inputStudents(std::vector<Student>& students) {
    int studentCount;
    std::cout << "Įveskite studentų skaičių: ";
    std::cin >> studentCount;
    
    students.reserve(studentCount); // Reserve space for efficiency
    
    for (int i = 0; i < studentCount; i++) {
        Student student;
        std::cout << "Vardas ir pavardė: ";
        std::cin >> student.vardas >> student.pavarde;
        
        char inputChoice;
        std::cout << "Ar norite įvesti namų darbų rezultatus rankiniu būdu? (y/n): ";
        std::cin >> inputChoice;
        
        if (inputChoice == 'y' || inputChoice == 'Y') {
            int homework;
            std::cout << "Suveskite namų darbų pažymius (-1 to finish): ";
            while (true) {
                std::cin >> homework;
                if (homework == -1) break;
                if (homework >= 0 && homework <= 10) { 
                    student.nd.push_back(homework);
                } else {
                    std::cout << "Neteisingas pažymys. Įveskite skaičių nuo 0 iki 10." << std::endl;
                }
            }
        } else {
            // random grades
            int numGrades = 5 + rand() % 6; // 5-10 random grades
            student.nd.reserve(numGrades);
            for (int j = 0; j < numGrades; j++) {
                student.nd.push_back(rand() % 11); // 0-10 grades
            }
            std::cout << "Sugeneruota " << numGrades << " atsitiktinių pažymių." << std::endl;
        }
        
        std::cout << "Ar norite įvesti egzamino rezultatą rankiniu būdu? (y/n): ";
        std::cin >> inputChoice;
        
        if (inputChoice == 'y' || inputChoice == 'Y') {
            std::cout << "Suveskite egzamino pažymį: ";
            std::cin >> student.egzaminas;
            while (student.egzaminas < 0 || student.egzaminas > 10) {
                std::cout << "Neteisingas pažymys. Įveskite skaičių nuo 0 iki 10: ";
                std::cin >> student.egzaminas;
            }
        } else {
            //random exam grade
            student.egzaminas = rand() % 11; // 0-10 grade
            std::cout << "Sugeneruotas egzamino pažymys: " << student.egzaminas << std::endl;
        }
        
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

bool compareByName(const Student& a, const Student& b) {
    return a.pavarde < b.pavarde;
}

int main() {
    srand(time(nullptr));
    
    std::vector<Student> students;
    char programChoice;
    
    std::cout << "Ar norite nuskaityti duomenis iš failo? (y/n): ";
    std::cin >> programChoice;
    
    if (programChoice == 'y' || programChoice == 'Y') {

        std::cout << "Failų skaitymo funkcionalumas dar nerealizuotas." << std::endl;
        inputStudents(students);
    } else {
        // Manual input
        inputStudents(students);
    }
    
    if (students.empty()) {
        std::cerr << "Nesuvesti studento duomenys!" << std::endl;
        return 1;
    }
    
    int sortOption;
    std::cout << "Pasirinkite pagal ką norite rušiuoti:" << std::endl;
    std::cout << "1 - Pavarde" << std::endl;
    std::cout << "2 - Vidurkiu" << std::endl;
    std::cout << "3 - Mediana" << std::endl;
    std::cout << "4 - Baigti darbą" << std::endl;
    std::cin >> sortOption;
    
    switch (sortOption) {
        case 1:
            std::sort(students.begin(), students.end(), compareByName);
            break;
        case 2:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.galutinisVid > b.galutinisVid;
            });
            break;
        case 3:
            std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.galutinisMed > b.galutinisMed;
            });
            break;
        case 4:
            std::cout << "Programa baigia darbą." << std::endl;
            return 0;
        default:
            std::cout << "Neteisingas pasirinkimas, rūšiuojama pagal pavardę." << std::endl;
            std::sort(students.begin(), students.end(), compareByName);
    }
    
    printResults(students);
    return 0;
}
