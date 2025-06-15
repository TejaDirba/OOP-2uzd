#include "Student.h"
#include "FileManager.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <exception>
#include <chrono>
using namespace std;
using Clock = chrono::high_resolution_clock;

void printMainMenu(){
    cout<<"\n=== STUDENTU PAZYMIU SISTEMA v1.1 ===\n"
          "1) Interactive mode\n"
          "2) Batch mode\n"
          "3) Generate test files\n"
          "4) Exit\n"
          "Choice: ";
}
int askIntInRange(const string& p,int lo,int hi){
    int x;
    while(true){
        cout<<p;
        if(cin>>x && x>=lo && x<=hi) return x;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Netinkamas\n";
    }
}
string askFileName(){
    cout<<"Failo pavadinimas: ";
    string s; cin>>s; return s;
}

template<typename C>
void runInteractiveOnce(int strat,const string& fn){
    C cont;
    FileManager::readIntoContainer(fn,cont);
    auto ts=Clock::now();
    if constexpr(is_same_v<C,vector<Student>>||is_same_v<C,deque<Student>>)
        sort(cont.begin(),cont.end(),compareByName);
    else
        cont.sort(compareByName);
    auto te=Clock::now();
    auto su=chrono::duration_cast<chrono::microseconds>(te-ts).count();
    cout<<"Rusiuoti uztruko "<<su<<" us\n";
    auto doSplit=[&](auto f,auto p){
        auto t2=Clock::now();
        f();
        auto t3=Clock::now();
        cout<<"Split uztruko "<<chrono::duration_cast<chrono::microseconds>(t3-t2).count()<<" us\n";
        string bext=fn.substr(0,fn.find_last_of('.'));
        FileManager::writeResultsToFile(f(),bext+"_fail.txt");
        FileManager::writeResultsToFile(p(),bext+"_pass.txt");
    };
    if constexpr(is_same_v<C,vector<Student>>){
        if(strat==1){
            vector<Student> f,p;
            FileManager::splitStrategy1_Vector(cont,f,p);
            doSplit([&]{return f;},[&]{return p;});
        } else {
            vector<Student> f;
            FileManager::splitStrategy2_Vector(cont,f);
            doSplit([&]{return f;},[&]{return cont;});
        }
    } else if constexpr(is_same_v<C,list<Student>>){
        if(strat==1){
            list<Student> f,p;
            FileManager::splitStrategy1_List(cont,f,p);
            vector<Student> fv(f.begin(),f.end()), pv(p.begin(),p.end());
            doSplit([&]{return fv;},[&]{return pv;});
        } else {
            list<Student> f;
            FileManager::splitStrategy2_List(cont,f);
            vector<Student> fv(f.begin(),f.end()), pv(cont.begin(),cont.end());
            doSplit([&]{return fv;},[&]{return pv;});
        }
    } else {
        if(strat==1){
            deque<Student> f,p;
            FileManager::splitStrategy1_Deque(cont,f,p);
            vector<Student> fv(f.begin(),f.end()), pv(p.begin(),p.end());
            doSplit([&]{return fv;},[&]{return pv;});
        } else {
            deque<Student> f;
            FileManager::splitStrategy2_Deque(cont,f);
            vector<Student> fv(f.begin(),f.end()), pv(cont.begin(),cont.end());
            doSplit([&]{return fv;},[&]{return pv;});
        }
    }
}

void runBatch(){
    vector<string> files={"test_1000.txt","test_10000.txt","test_100000.txt","test_1000000.txt","test_10000000.txt"};
    double sum=0; int runs=0;
    for(int ct=1;ct<=3;++ct)for(int s=1;s<=2;++s){
        cout<<"\n>> Container="<<ct<<" Strat="<<s<<"\n";
        for(auto& fn:files){
            auto rs=Clock::now();
            try{
                if(ct==1){
                    vector<Student>d;
                    FileManager::readIntoContainer(fn,d);
                    sort(d.begin(),d.end(),compareByName);
                    if(s==1){
                        vector<Student>f,p;
                        FileManager::splitStrategy1_Vector(d,f,p);
                        FileManager::writeResultsToFile(f,fn.substr(0,fn.find_last_of('.'))+"_fail.txt");
                        FileManager::writeResultsToFile(p,fn.substr(0,fn.find_last_of('.'))+"_pass.txt");
                    } else {
                        vector<Student>f;
                        FileManager::splitStrategy2_Vector(d,f);
                        FileManager::writeResultsToFile(f,fn.substr(0,fn.find_last_of('.'))+"_fail.txt");
                        FileManager::writeResultsToFile(d,fn.substr(0,fn.find_last_of('.'))+"_pass.txt");
                    }
                } else if(ct==2){
                    list<Student>d;
                    FileManager::readIntoContainer(fn,d);
                    d.sort(compareByName);
                    if(s==1){
                        list<Student>f,p;
                        FileManager::splitStrategy1_List(d,f,p);
                        vector<Student>fv(f.begin(),f.end()),pv(p.begin(),p.end());
                        FileManager::writeResultsToFile(fv,fn.substr(0,fn.find_last_of('.'))+"_fail.txt");
                        FileManager::writeResultsToFile(pv,fn.substr(0,fn.find_last_of('.'))+"_pass.txt");
                    } else {
                        list<Student>f;
                        FileManager::splitStrategy2_List(d,f);
                        vector<Student>fv(f.begin(),f.end()),pv(d.begin(),d.end());
                        FileManager::writeResultsToFile(fv,fn.substr(0,fn.find_last_of('.'))+"_fail.txt");
                        FileManager::writeResultsToFile(pv,fn.substr(0,fn.find_last_of('.'))+"_pass.txt");
                    }
                } else {
                    deque<Student>d;
                    FileManager::readIntoContainer(fn,d);
                    sort(d.begin(),d.end(),compareByName);
                    if(s==1){
                        deque<Student>f,p;
                        FileManager::splitStrategy1_Deque(d,f,p);
                        vector<Student>fv(f.begin(),f.end()),pv(p.begin(),p.end());
                        FileManager::writeResultsToFile(fv,fn.substr(0,fn.find_last_of('.'))+"_fail.txt");
                        FileManager::writeResultsToFile(pv,fn.substr(0,fn.find_last_of('.'))+"_pass.txt");
                    } else {
                        deque<Student>f;
                        FileManager::splitStrategy2_Deque(d,f);
                        vector<Student>fv(f.begin(),f.end()),pv(d.begin(),d.end());
                        FileManager::writeResultsToFile(fv,fn.substr(0,fn.find_last_of('.'))+"_fail.txt");
                        FileManager::writeResultsToFile(pv,fn.substr(0,fn.find_last_of('.'))+"_pass.txt");
                    }
                }
            }catch(const exception& e){
                cerr<<"Error "<<fn<<": "<<e.what()<<"\n";
            }
            auto re=Clock::now();
            auto us=chrono::duration_cast<chrono::microseconds>(re-rs).count();
            cout<<fn<<" "<<us<<" us\n";
            sum+=us; ++runs;
        }
    }
    if(runs)cout<<"\nAvg: "<<(sum/runs)<<" us\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(true){
        printMainMenu();
        int c;
        if(!(cin>>c)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');continue;}
        if(c==1){
            int ct=askIntInRange("1=vec,2=list,3=deque: ",1,3);
            int s=askIntInRange("Strat(1/2): ",1,2);
            string fn=askFileName();
            if(ct==1) runInteractiveOnce<vector<Student>>(s,fn);
            else if(ct==2) runInteractiveOnce<list<Student>>(s,fn);
            else runInteractiveOnce<deque<Student>>(s,fn);
        } else if(c==2){
            runBatch();
        } else if(c==3){
            FileManager::generateTestFiles();
            cout<<"Test files generated\n";
        } else if(c==4){
            return 0;
        }
    }
}
