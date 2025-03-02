#include "utils.h"

double calculateAverage(const vector<int>& paz) {
    if (paz.empty()) return 0;
    return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

double calculateMedian(vector<int> paz) {
    if (paz.empty()) return 0;
    std::sort(paz.begin(), paz.end());
    size_t size = paz.size();
    return (size % 2 == 0) ? (paz[size / 2 - 1] + paz[size / 2]) / 2.0 : paz[size / 2];
}

bool compareByName(const Stud& a, const Stud& b) {
    return a.var < b.var;
}

bool compareByAvg(const Stud& a, const Stud& b) {
    return a.galutinisVid > b.galutinisVid;
}

bool compareByMedian(const Stud& a, const Stud& b) {
    return a.galutinisMed > b.galutinisMed;
}
