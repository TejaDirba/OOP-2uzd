#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <random>
#include <ctime>

// Student structure for std::vector version
struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
};

// Student structure for mixed version (C arrays + std::vector)
struct StudentArray {
    std::string vardas;
    std::string pavarde;
    int nd[20]; // maksimalus namų darbų skaičius
    int ndCount;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
};

int getValidGrade(const std::string& prompt) {
    int grade;
    while (true) {
        std::cout << prompt;
        std::cin >> grade;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Klaida: Įveskite skaičių!\n";
            continue;
        }
        if (grade >= 0 && grade <= 10) {
            return grade;
        }
        std::cout << "Klaida: Pažymys turi būti 0-10 intervale!\n";
    }
}

int getHomeworkGrade(const std::string& prompt) {
    int grade;
    while (true) {
        std::cout << prompt;
        std::cin >> grade;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Klaida: Įveskite skaičių!\n";
            continue;
        }
        if (grade == -1) {
            return -1; // terminate input
        }
        if (grade >= 0 && grade <= 10) {
            return grade;
        }
        std::cout << "Klaida: Pažymys turi būti 0-10 intervale arba -1 baigimui!\n";
    }
}

int getValidStudentCount() {
    int count;
    while (true) {
        std::cout << "Įveskite studentų skaičių: ";
        std::cin >> count;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Klaida: Įveskite skaičių!\n";
            continue;
        }
        if (count > 0) {
            return count;
        }
        std::cout << "Klaida: Studentų skaičius turi būti teigiamas!\n";
    }
}

int getValidHomeworkCount() {
    int count;
    while (true) {
        std::cout << "Kiek namų darbų pažymių generuoti? ";
        std::cin >> count;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Klaida: Įveskite skaičių!\n";
            continue;
        }
        if (count >= 0 && count <= 20) {
            return count;
        }
        std::cout << "Klaida: Namų darbų skaičius turi būti 0-20 intervale!\n";
    }
}

int getValidMenuChoice(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Klaida: Įveskite skaičių!\n";
            std::cout << "Pasirinkite (" << min << "-" << max << "): ";
            continue;
        }
        if (choice >= min && choice <= max) {
            return choice;
        }
        std::cout << "Neteisingas pasirinkimas! Pasirinkite " << min << "-" << max << ".\n";
        std::cout << "Pasirinkite (" << min << "-" << max << "): ";
    }
}

// Calculation functions for std::vector
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

// Calculation functions for C arrays
double calculateAverageArray(const int nd[], int count) {
    if (count == 0) return 0;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += nd[i];
    }
    return static_cast<double>(sum) / count;
}

double calculateMedianArray(int nd[], int count) {
    if (count == 0) return 0;
    std::sort(nd, nd + count);
    if (count % 2 == 0) 
        return (nd[count / 2 - 1] + nd[count / 2]) / 2.0;
    else 
        return nd[count / 2];
}


std::vector<std::string> vardai = {
    "Jonas", "Jonukas", "Jonukelis", "Jonuliukas", "Jonce", "Une", 
    "Kazys", "Vytautas", "Jurgis", "Aldona", "Rasa", "Dalia"
};

std::vector<std::string> pavardes = {
    "Petraitis", "Jonaitis", "Kazlauskas", "Jankaitis", "Urbanavičius", 
    "Paulauskas", "Kvedaras", "Balčiūnas", "Rimkus", "Vasiliauskas"
};

std::string generateRandomName() {
    return vardai[rand() % vardai.size()];
}

std::string generateRandomSurname() {
    return pavardes[rand() % pavardes.size()];
}

int generateRandomGrade() {
    return rand() % 11; // 0-10
}

// Option 1: Manual input (std::vector version)
void inputStudentsManual(std::vector<Student>& students) {
    int studentCount = getValidStudentCount();
    
    for (int i = 0; i < studentCount; i++) {
        Student student;
        std::cout << "\n--- Studentas " << (i + 1) << " ---\n";
        std::cout << "Vardas: ";
        std::cin >> student.vardas;
        std::cout << "Pavardė: ";
        std::cin >> student.pavarde;
        
        std::cout << "Įveskite namų darbų pažymius (-1 baigti):\n";
        int homework;
        while (true) {
            homework = getHomeworkGrade("Namų darbas: ");
            if (homework == -1) break;
            student.nd.push_back(homework);
        }
        
        student.egzaminas = getValidGrade("Egzamino pažymys: ");
        
        student.galutinisVid = 0.4 * calculateAverage(student.nd) + 0.6 * student.egzaminas;
        student.galutinisMed = 0.4 * calculateMedian(student.nd) + 0.6 * student.egzaminas;
        
        students.push_back(student);
    }
}

// Option 2: generate grades only (std::vector version)
void generateGradesOnly(std::vector<Student>& students) {
    int studentCount = getValidStudentCount();
    
    for (int i = 0; i < studentCount; i++) {
        Student student;
        std::cout << "\n--- Studentas " << (i + 1) << " ---\n";
        std::cout << "Vardas: ";
        std::cin >> student.vardas;
        std::cout << "Pavardė: ";
        std::cin >> student.pavarde;
        
        int homeworkCount = getValidHomeworkCount();
        
        std::cout << "Sugeneruoti namų darbų pažymiai: ";
        for (int j = 0; j < homeworkCount; j++) {
            int grade = generateRandomGrade();
            student.nd.push_back(grade);
            std::cout << grade << " ";
        }
        
        student.egzaminas = generateRandomGrade();
        std::cout << "\nSugeneruotas egzamino pažymys: " << student.egzaminas << std::endl;
        
        student.galutinisVid = 0.4 * calculateAverage(student.nd) + 0.6 * student.egzaminas;
        student.galutinisMed = 0.4 * calculateMedian(student.nd) + 0.6 * student.egzaminas;
        
        students.push_back(student);
    }
}

// Option 3: generate everything (std::vector version)
void generateEverything(std::vector<Student>& students) {
    int studentCount = getValidStudentCount();
    
    for (int i = 0; i < studentCount; i++) {
        Student student;
        student.vardas = generateRandomName();
        student.pavarde = generateRandomSurname();
        
        int homeworkCount = 3 + (rand() % 8); // 3-10 namų darbų
        for (int j = 0; j < homeworkCount; j++) {
            student.nd.push_back(generateRandomGrade());
        }
        
        student.egzaminas = generateRandomGrade();
        student.galutinisVid = 0.4 * calculateAverage(student.nd) + 0.6 * student.egzaminas;
        student.galutinisMed = 0.4 * calculateMedian(student.nd) + 0.6 * student.egzaminas;
        
        students.push_back(student);
        
        std::cout << "Sugeneruotas studentas: " << student.vardas << " " << student.pavarde << std::endl;
    }
}

// Manual input for mixed version (C arrays)
void inputStudentsMixed(std::vector<StudentArray>& students) {
    int studentCount = getValidStudentCount();
    
    for (int i = 0; i < studentCount; i++) {
        StudentArray student;
        std::cout << "\n--- Studentas " << (i + 1) << " ---\n";
        std::cout << "Vardas: ";
        std::cin >> student.vardas;
        std::cout << "Pavardė: ";
        std::cin >> student.pavarde;
        
        student.ndCount = 0;
        std::cout << "Įveskite namų darbų pažymius (-1 baigti):\n";
        int homework;
        while (student.ndCount < 20) {
            homework = getHomeworkGrade("Namų darbas: ");
            if (homework == -1) break;
            student.nd[student.ndCount] = homework;
            student.ndCount++;
        }
        
        student.egzaminas = getValidGrade("Egzamino pažymys: ");
        
        // Create temporary array for median calculation
        int tempArray[20];
        for (int j = 0; j < student.ndCount; j++) {
            tempArray[j] = student.nd[j];
        }
        
        student.galutinisVid = 0.4 * calculateAverageArray(student.nd, student.ndCount) + 0.6 * student.egzaminas;
        student.galutinisMed = 0.4 * calculateMedianArray(tempArray, student.ndCount) + 0.6 * student.egzaminas;
        
        students.push_back(student);
    }
}

// Print results for std::vector version
void printResults(const std::vector<Student>& students) {
    std::cout << "\n" << std::left << std::setw(15) << "Pavardė" 
              << std::setw(15) << "Vardas" 
              << std::setw(18) << "Galutinis (Vid.)"
              << std::setw(18) << "Galutinis (Med.)"
              << "\n" << std::string(66, '-') << "\n";
    
    for (const auto& student : students) {
        std::cout << std::left << std::setw(15) << student.pavarde
                  << std::setw(15) << student.vardas
                  << std::setw(18) << std::fixed << std::setprecision(2) << student.galutinisVid
                  << std::setw(18) << std::fixed << std::setprecision(2) << student.galutinisMed
                  << std::endl;
    }
}

// Print results for mixed version (C arrays)
void printResultsMixed(const std::vector<StudentArray>& students) {
    std::cout << "\n" << std::left << std::setw(15) << "Pavardė" 
              << std::setw(15) << "Vardas" 
              << std::setw(18) << "Galutinis (Vid.)"
              << std::setw(18) << "Galutinis (Med.)"
              << "\n" << std::string(66, '-') << "\n";
    
    for (const auto& student : students) {
        std::cout << std::left << std::setw(15) << student.pavarde
                  << std::setw(15) << student.vardas
                  << std::setw(18) << std::fixed << std::setprecision(2) << student.galutinisVid
                  << std::setw(18) << std::fixed << std::setprecision(2) << student.galutinisMed
                  << std::endl;
    }
}

// Comparator functions
bool compareByName(const Student& a, const Student& b) {
    return a.vardas < b.vardas;
}

bool compareByNameArray(const StudentArray& a, const StudentArray& b) {
    return a.vardas < b.vardas;
}

void showMenu() {
    std::cout << "\n=== Pasirinkite ===\n";
    std::cout << "1 - Įvesti duomenis ranką\n";
    std::cout << "2 - Generuoti tik pažymius\n";
    std::cout << "3 - Generuoti studentų vardus, pavardes ir pažymius\n";
    std::cout << "4 - Baigti darbą\n";
    std::cout << "Pasirinkite (1-4): ";
}

void showVersionMenu() {
    std::cout << "=== Pasirinkite ===\n";
    std::cout << "1 - std::vector versija\n";
    std::cout << "2 - Mišri versija (C masyvai + std::vector)\n";
    std::cout << "Pasirinkite (1-2): ";
}

int main() {
    std::srand(std::time(nullptr));
    
    int versionChoice;
    showVersionMenu();
    versionChoice = getValidMenuChoice(1, 2);
    
    if (versionChoice == 1) {
        // std::vector versija - naudoja tik std::vector konteinerius
        std::vector<Student> students;
        
        while (true) {
            showMenu();
            int choice = getValidMenuChoice(1, 4);
            
            switch (choice) {
                case 1:
                    students.clear();
                    inputStudentsManual(students);
                    break;
                case 2:
                    students.clear();
                    generateGradesOnly(students);
                    break;
                case 3:
                    students.clear();
                    generateEverything(students);
                    break;
                case 4:
                    std::cout << "Programa baigta.\n";
                    return 0;
            }
            
            if (!students.empty()) {
                std::cout << "\nPasirinkite rūšiavimą (1-Vardas, 2-Vidurkis, 3-Mediana): ";
                int sortOption = getValidMenuChoice(1, 3);
                
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
            }
        }
    } 
    else if (versionChoice == 2) {
        // Mišri versija - naudoja C masyvus ir std::vector
        std::vector<StudentArray> students;
        
        while (true) {
            showMenu();
            int choice = getValidMenuChoice(1, 4);
            
            switch (choice) {
                case 1:
                    students.clear();
                    inputStudentsMixed(students);
                    break;
                case 2:
                case 3:
                    std::cout << "Šie pasirinkimai palaikomi tik std::vector versijoje.\n";
                    continue;
                case 4:
                    std::cout << "Programa baigta.\n";
                    return 0;
            }
            
            if (!students.empty()) {
                std::cout << "\nPasirinkite rūšiavimą (1-Vardas, 2-Vidurkis, 3-Mediana): ";
                int sortOption = getValidMenuChoice(1, 3);
                
                if (sortOption == 1) {
                    std::sort(students.begin(), students.end(), compareByNameArray);
                } else if (sortOption == 2) {
                    std::sort(students.begin(), students.end(), [](const StudentArray& a, const StudentArray& b) {
                        return a.galutinisVid > b.galutinisVid;
                    });
                } else if (sortOption == 3) {
                    std::sort(students.begin(), students.end(), [](const StudentArray& a, const StudentArray& b) {
                        return a.galutinisMed > b.galutinisMed;
                    });
                }
                
                printResultsMixed(students);
            }
        }
    }
    
    return 0;
}
