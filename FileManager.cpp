#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <chrono>
#include <random>

using namespace std;
using Clock = chrono::high_resolution_clock;

struct Timer {
    string name;
    Clock::time_point start;
    Timer(const string& n): name(n), start(Clock::now()) {}
    ~Timer() {
        auto stop = Clock::now();
        auto us = chrono::duration_cast<chrono::microseconds>(stop - start).count();
        cout << name << " uztruko " << us << " us\n";
    }
};

vector<Student> FileManager::readStudentsFromFile(const string& fn) {
    Timer t("Skaitymas[" + fn + "]");
    ifstream f(fn);
    if (!f) throw runtime_error("Cannot open " + fn);
    string line;
    getline(f, line);
    vector<Student> out; int cnt = 0;
    auto cs = Clock::now();
    while (getline(f, line)) {
        if (line.empty()) continue;
        try {
            Student s;
            stringstream ss(line);
            ss >> s;
            int g; vector<int> all;
            while (ss >> g) all.push_back(g);
            s.setNd({ all.begin(), all.end() - 1 });
            s.setEgzaminas(all.back());
            s.calculateFinalGrades();
            out.push_back(move(s)); ++cnt;
        } catch (...) {}
    }
    auto us = chrono::duration_cast<chrono::microseconds>(Clock::now() - cs).count();
    cout << "Calc " << cnt << " took " << us << " us\n";
    if (out.empty()) throw runtime_error("No valid");
    return out;
}

void FileManager::writeResultsToFile(const vector<Student>& v, const string& fn) {
    Timer t("Rasymas[" + fn + "]");
    ofstream o(fn);
    if (!o) throw runtime_error("Cannot create " + fn);
    o << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
      << setw(15) << "Vid" << setw(15) << "Med\n"
      << string(60, '-') << "\n";
    for (auto const& s : v) o << s << "\n";
}

void FileManager::printHeader() {
    cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
         << setw(15) << "Vid" << setw(15) << "Med\n"
         << string(60, '-') << "\n";
}

void FileManager::printResults(const vector<Student>& v) {
    printHeader();
    for (auto const& s : v) cout << s << "\n";
}

void FileManager::splitAndWriteVector(const vector<Student>& all, const string& b) {
    vector<Student> f, p;
    for (auto const& s : all) (s.getGalutinisVid() < 5 ? f : p).push_back(s);
    writeResultsToFile(f, b + "_fail.txt");
    writeResultsToFile(p, b + "_pass.txt");
}

void FileManager::splitAndWriteList(const list<Student>& all, const string& b) {
    list<Student> f, p;
    for (auto const& s : all) (s.getGalutinisVid() < 5 ? f : p).push_back(s);
    writeResultsToFile({ f.begin(), f.end() }, b + "_fail.txt");
    writeResultsToFile({ p.begin(), p.end() }, b + "_pass.txt");
}

void FileManager::splitAndWriteDeque(const deque<Student>& all, const string& b) {
    deque<Student> f, p;
    for (auto const& s : all) (s.getGalutinisVid() < 5 ? f : p).push_back(s);
    writeResultsToFile({ f.begin(), f.end() }, b + "_fail.txt");
    writeResultsToFile({ p.begin(), p.end() }, b + "_pass.txt");
}

template<typename C>
void FileManager::readIntoContainer(const string& fn, C& out) {
    auto v = readStudentsFromFile(fn);
    for (auto&& s : v) out.push_back(move(s));
}

template void FileManager::readIntoContainer<vector<Student>>(const string&, vector<Student>&);
template void FileManager::readIntoContainer<list<Student>>(const string&, list<Student>&);
template void FileManager::readIntoContainer<deque<Student>>(const string&, deque<Student>&);

void FileManager::splitStrategy1_Vector(const vector<Student>& data, vector<Student>& fail, vector<Student>& pass) {
    splitAndWriteVector(data, "tmp");
}

void FileManager::splitStrategy2_Vector(vector<Student>& data, vector<Student>& fail) {
    splitStrategy1_Vector(data, fail, data);
}

void FileManager::splitStrategy1_List(const list<Student>& data, list<Student>& fail, list<Student>& pass) {}

void FileManager::splitStrategy2_List(list<Student>& data, list<Student>& fail) {}

void FileManager::splitStrategy1_Deque(const deque<Student>& data, deque<Student>& fail, deque<Student>& pass) {}

void FileManager::splitStrategy2_Deque(deque<Student>& data, deque<Student>& fail) {}

void FileManager::generateTestFiles() {
    vector<size_t> sz = {1000, 10000, 100000};
    mt19937_64 rng(random_device{}());
    uniform_int_distribution<int> gd(0,10), cnt(3,10);
    for (auto N : sz) {
        string fn = "test_" + to_string(N) + ".txt";
        ofstream o(fn);
        o << "vardas pavarde nd... egz\n";
        for (size_t i = 0; i < N; i++) {
            o << "V" << i << " P" << i;
            for (int k = 0; k < cnt(rng); k++) o << " " << gd(rng);
            o << " " << gd(rng) << "\n";
        }
    }
}
