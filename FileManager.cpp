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
    Timer(const string& n):name(n),start(Clock::now()){}
    ~Timer(){
        auto stop=Clock::now();
        auto us=chrono::duration_cast<chrono::microseconds>(stop-start).count();
        cout<<name<<" uztruko "<<us<<" us";
        if(us>1000)cout<<" ("<<fixed<<setprecision(2)<<(us/1000.0)<<" ms)";
        if(us>1000000)cout<<" ("<<fixed<<setprecision(3)<<(us/1e6)<<" s)";
        cout<<"\n";
    }
};
vector<Student> FileManager::readStudentsFromFile(const string& filename){
    Timer t("Skaitymas ["+filename+"]");
    vector<Student> v;
    ifstream f(filename);
    if(!f)throw runtime_error("Nepavyko atidaryti: "+filename);
    string line;
    if(!getline(f,line))throw runtime_error("Tuscias arba negalima perskaityti antrastes");
    int cnt=0;
    auto cs=Clock::now();
    while(getline(f,line)){
        if(line.empty())continue;
        try{
            Student s;
            parseStudentLine(line,s);
            s.calculateFinalGrades();
            v.push_back(move(s));
            ++cnt;
        }catch(const exception& e){
            cerr<<"    klaida: "<<e.what()<<"\n";
        }
    }
    auto ce=Clock::now();
    auto us=chrono::duration_cast<chrono::microseconds>(ce-cs).count();
    cout<<"Galutiniu skaiciavimas "<<cnt<<" uztruko "<<us<<" us\n";
    if(v.empty())throw runtime_error("Nerasta studentu");
    return v;
}
void FileManager::parseStudentLine(const string& line,Student& s){
    stringstream ss(line);
    string v,p;
    if(!(ss>>v>>p))throw invalid_argument("V/P");
    s.setVardas(v);
    s.setPavarde(p);
    vector<int> all;
    int g;
    while(ss>>g){
        if(!isValidGrade(g))throw invalid_argument("Netinkamas:"+to_string(g));
        all.push_back(g);
    }
    if(all.empty())throw invalid_argument("Nerasta pazymiu");
    s.setEgzaminas(all.back());
    all.pop_back();
    if(all.empty())throw invalid_argument("Nera ND");
    s.setNd(all);
}
bool FileManager::isValidGrade(int g){return g>=0&&g<=10;}
void FileManager::writeResultsToFile(const vector<Student>& data,const string& fn){
    Timer t("Rasymas ["+fn+"]");
    ofstream o(fn);
    if(!o)throw runtime_error("Nepavyko sukurti:"+fn);
    o<<left<<setw(15)<<"Pavarde"<<setw(15)<<"Vardas"<<setw(15)<<"GalFinal(Vid)"<<setw(15)<<"GalFinal(Med)"<<"\n"<<string(60,'-')<<"\n";
    for(auto const& s:data)o<<s<<"\n";
    cout<<"Rezultatai i: "<<fn<<"\n";
}
void FileManager::printHeader(){
    cout<<left<<setw(15)<<"Pavarde"<<setw(15)<<"Vardas"<<setw(15)<<"GalFinal(Vid)"<<setw(15)<<"GalFinal(Med)"<<"\n"<<string(60,'-')<<"\n";
}
void FileManager::printResults(const vector<Student>& v){
    printHeader();
    for(auto const& s:v)cout<<s<<"\n";
}
void FileManager::splitAndWriteVector(const vector<Student>& all,const string& base){
    Timer t("SplitVec&Write["+base+"]");
    vector<Student> f,p;
    for(auto const& s:all){
        if(s.getGalutinisVid()<5.0)f.push_back(s);
        else p.push_back(s);
    }
    auto noext=base.substr(0,base.find_last_of('.'));
    writeResultsToFile(f,noext+"_fail.txt");
    writeResultsToFile(p,noext+"_pass.txt");
}
void FileManager::splitAndWriteList(const list<Student>& all,const string& base){
    Timer t("SplitList&Write["+base+"]");
    list<Student> f,p;
    for(auto const& s:all){
        if(s.getGalutinisVid()<5.0)f.push_back(s);
        else p.push_back(s);
    }
    vector<Student> fv(f.begin(),f.end()), pv(p.begin(),p.end());
    auto noext=base.substr(0,base.find_last_of('.'));
    writeResultsToFile(fv,noext+"_fail.txt");
    writeResultsToFile(pv,noext+"_pass.txt");
}
void FileManager::splitAndWriteDeque(const deque<Student>& all,const string& base){
    Timer t("SplitDeq&Write["+base+"]");
    deque<Student> f,p;
    for(auto const& s:all){
        if(s.getGalutinisVid()<5.0)f.push_back(s);
        else p.push_back(s);
    }
    vector<Student> fv(f.begin(),f.end()), pv(p.begin(),p.end());
    auto noext=base.substr(0,base.find_last_of('.'));
    writeResultsToFile(fv,noext+"_fail.txt");
    writeResultsToFile(pv,noext+"_pass.txt");
}
template<typename C>
void FileManager::readIntoContainer(const string& filename,C& out){
    Timer t("Skaitymas["+filename+"]");
    ifstream f(filename);
    if(!f)throw runtime_error("Nepavyko atidaryti:"+filename);
    string line;
    if(!getline(f,line))throw runtime_error("Tuscias arba neina header");
    int cnt=0;
    auto cs=Clock::now();
    while(getline(f,line)){
        if(line.empty())continue;
        try{
            Student s;
            parseStudentLine(line,s);
            s.calculateFinalGrades();
            out.push_back(move(s));
            ++cnt;
        }catch(const exception& e){
            cerr<<"    klaida: "<<e.what()<<"\n";
        }
    }
    auto ce=Clock::now();
    auto us=chrono::duration_cast<chrono::microseconds>(ce-cs).count();
    cout<<"Galutiniu skaiciavimas "<<cnt<<" uztruko "<<us<<" us\n";
    if(cnt==0)throw runtime_error("Nerasta");
}
template void FileManager::readIntoContainer<vector<Student>>(const string&,vector<Student>&);
template void FileManager::readIntoContainer<list<Student>>(const string&,list<Student>&);
template void FileManager::readIntoContainer<deque<Student>>(const string&,deque<Student>&);
void FileManager::splitStrategy1_Vector(const vector<Student>& data,vector<Student>& fail,vector<Student>& pass){
    fail.clear(); pass.clear();
    for(auto const& s:data){
        if(s.getGalutinisVid()<5.0)fail.push_back(s);
        else pass.push_back(s);
    }
}
void FileManager::splitStrategy2_Vector(vector<Student>& data,vector<Student>& fail){
    fail.clear();
    auto it=stable_partition(data.begin(),data.end(),[](auto const& s){return s.getGalutinisVid()<5.0;});
    fail.assign(data.begin(),it);
    data.erase(data.begin(),it);
}
void FileManager::splitStrategy1_List(const list<Student>& data,list<Student>& fail,list<Student>& pass){
    fail.clear(); pass.clear();
    for(auto const& s:data){
        if(s.getGalutinisVid()<5.0)fail.push_back(s);
        else pass.push_back(s);
    }
}
void FileManager::splitStrategy2_List(list<Student>& data,list<Student>& fail){
    fail.clear();
    for(auto it=data.begin();it!=data.end();){
        if(it->getGalutinisVid()<5.0){
            auto mv=it++;
            fail.splice(fail.end(),data,mv);
        } else ++it;
    }
}
void FileManager::splitStrategy1_Deque(const deque<Student>& data,deque<Student>& fail,deque<Student>& pass){
    fail.clear(); pass.clear();
    for(auto const& s:data){
        if(s.getGalutinisVid()<5.0)fail.push_back(s);
        else pass.push_back(s);
    }
}
void FileManager::splitStrategy2_Deque(deque<Student>& data,deque<Student>& fail){
    fail.clear();
    deque<Student> kept;
    kept.reserve(data.size());
    for(auto const& s:data){
        if(s.getGalutinisVid()<5.0)fail.push_back(s);
        else kept.push_back(s);
    }
    data.swap(kept);
}
void FileManager::generateTestFiles(){
    vector<size_t> sizes={1000,10000,100000,1000000,10000000};
    mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
    auto randGrade=[&](){return uniform_int_distribution<int>(0,10)(rng);};
    auto randCount=[&](){return uniform_int_distribution<int>(3,10)(rng);};
    for(auto N:sizes){
        string fname="test_"+to_string(N)+".txt";
        Timer t("Kuriamas["+fname+"]");
        ofstream out(fname);
        if(!out){cerr<<"klaida kuriant "<<fname<<"\n"; continue;}
        out<<"vardas pavarde nd... egz\n";
        for(size_t i=1;i<=N;++i){
            out<<"Vardas"<<i<<" Pavarde"<<i;
            int c=randCount();
            for(int k=0;k<c;++k)out<<" "<<randGrade();
            out<<" "<<randGrade()<<"\n";
        }
    }
}
