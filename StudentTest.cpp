#include "Student.h"
#include <cassert>
#include <sstream>

int main() {
    Student a("Jonas","Jonaitis");
    a.setNd({8,10,7});
    a.setEgzaminas(9);
    a.calculateFinalGrades();
    double vid = a.getGalutinisVid();
    double med = a.getGalutinisMed();
    assert(vid > 0 && med > 0);

    Student b(a);
    assert(b.getVardas() == "Jonas");

    Student c(std::move(b));
    assert(c.getVardas() == "Jonas");

    Student d;
    d = a;
    assert(d.getPavarde() == "Jonaitis");

    Student e;
    e = std::move(d);
    assert(e.getEgzaminas() == 9);

    std::stringstream ss;
    ss << c;
    Student f;
    ss >> f;
    assert(f.getVardas() == c.getVardas());

    std::cout << "All Student tests OK\n";
    return 0;
}
