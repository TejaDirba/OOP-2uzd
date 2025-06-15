#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vardas;
    std::string pavarde;
public:
    Zmogus(const std::string& v, const std::string& p);
    std::string getVardas() const;
    std::string getPavarde() const;
    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);
    virtual ~Zmogus() = 0;
};

inline Zmogus::~Zmogus() {}

#endif
