#include "Student.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <stdexcept>

// Zmogus implementations
Zmogus::Zmogus(const std::string& v, const std::string& p)
    : vardas(v), pavarde(p) {}
std::string Zmogus::getVardas() const { return vardas; }
std::string Zmogus::getPavarde() const { return pavarde; }
void Zmogus::setVardas(const std::string& v) {
    if (v.empty()) throw std::invalid_argument("Vardas negali buti tuscias");
    vardas = v;
}
void Zmogus::setPavarde(const std::string& p) {
    if (p.empty()) throw std::invalid_argument("Pavarde negali buti tuscia");
    pavarde = p;
}

// Student implementations
Student::Student()
    : Zmogus("",""), nd(), egzaminas(0), galutinisVid(0), galutinisMed(0) {}
Student::Student(const std::string& v, const std::string& p)
    : Zmogus(v,p), nd(), egzaminas(0), galutinisVid(0), galutinisMed(0) {}

Student::Student(const Student& o)
    : Zmogus(o), nd(o.nd), egzaminas(o.egzaminas),
      galutinisVid(o.galutinisVid), galutinisMed(o.galutinisMed) {}

Student::Student(Student&& o) noexcept
    : Zmogus(std::move(o)), nd(std::move(o.nd)), egzaminas(o.egzaminas),
      galutinisVid(o.galutinisVid), galutinisMed(o.galutinisMed) {
    o.egzaminas = 0;
    o.galutinisVid = o.galutinisMed = 0;
}

Student& Student::operator=(const Student& o) {
    if (this != &o) {
        setVardas(o.getVardas());
        setPavarde(o.getPavarde());
        nd = o.nd;
        egzaminas = o.egzaminas;
        galutinisVid = o.galutinisVid;
        galutinisMed = o.galutinisMed;
    }
    return *this;
}

Student& Student::operator=(Student&& o) noexcept {
    if (this != &o) {
        setVardas(std::move(o.vardas));
        setPavarde(std::move(o.pavarde));
        nd = std::move(o.nd);
        egzaminas = o.egzaminas;
        galutinisVid = o.galutinisVid;
        galutinisMed = o.galutinisMed;
        o.egzaminas = 0;
        o.galutinisVid = o.galutinisMed = 0;
    }
    return *this;
}

Student::~Student() {}

std::vector<int> Student::getNd() const { return nd; }
int Student::getEgzaminas() const { return egzaminas; }
double Student::getGalutinisVid() const { return galutinisVid; }
double Student::getGalutinisMed() const { return galutinisMed; }

void Student::setNd(const std::vector<int>& grades) {
    for (int g : grades) if (g<0||g>10) throw std::invalid_argument("ND netinkamas");
    nd = grades;
}
void Student::setEgzaminas(int e) {
    if (e<0||e>10) throw std::invalid_argument("Egzamino netinkamas");
    egzaminas = e;
}
void Student::addHomeworkGrade(int grade) {
    if (grade<0||grade>10) throw std::invalid_argument("Pazymys netinkamas");
    nd.push_back(grade);
}

void Student::calculateFinalGrades() {
    if (nd.empty()) throw std::logic_error("Nera ND");
    double sum = std::accumulate(nd.begin(), nd.end(), 0.0);
    double avg = sum / nd.size();
    auto tmp = nd; std::sort(tmp.begin(), tmp.end());
    double med = tmp.size()%2==0 ? (tmp[tmp.size()/2-1]+tmp[tmp.size()/2])/2.0
                                 : tmp[tmp.size()/2];
    galutinisVid = 0.4*avg + 0.6*egzaminas;
    galutinisMed = 0.4*med + 0.6*egzaminas;
}

bool compareByName(const Student& a, const Student& b) {
    return a.getVardas() < b.getVardas();
}
bool compareByAvg(const Student& a, const Student& b) {
    return a.getGalutinisVid() > b.getGalutinisVid();
}
bool compareByMedian(const Student& a, const Student& b) {
    return a.getGalutinisMed() > b.getGalutinisMed();
}

std::istream& operator>>(std::istream& is, Student& s) {
    std::string v, p;
    if (!(is>>v>>p)) throw std::runtime_error("I/O klaida");
    s.setVardas(v);
    s.setPavarde(p);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os<<std::left<<std::setw(15)<<s.getPavarde()
      <<std::setw(15)<<s.getVardas()
      <<std::setw(15)<<std::fixed<<std::setprecision(2)<<s.getGalutinisVid()
      <<std::setw(15)<<std::fixed<<std::setprecision(2)<<s.getGalutinisMed();
    return os;
}
