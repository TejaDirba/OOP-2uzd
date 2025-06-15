#include "FileManager.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <chrono>

using namespace std;
using Clock = chrono::high_resolution_clock;

void printMenu(){
    cout<<"\n=== STUDENTŲ SISTEMA ===\n"
          "1) Interactive\n"
          "2) Batch\n"
          "3) Generate tests\n"
          "4) Exit\n"
          "Choice: ";
}

int ask(int lo,int hi){
    int x;
    while(!(cin>>x) || x<lo||x>hi){
        cin.clear();
        cin.ignore(1e6,'\n');
        cout<<"Bad, try again: ";
    }
    return x;
}

string askFile(){
    cout<<"File name: ";
    string s; cin>>s;
    return s;
}

template<typename C>
void runOnce(int strat,const string& fn){
    C cont;
    FileManager::readIntoContainer(fn,cont);
    auto t1=Clock::now();
    if constexpr(is_same_v<C,vector<Student>>||is_same_v<C,deque<Student>>)
        sort(cont.begin(),cont.end(),compareByName);
    else
        cont.sort(compareByName);
    cout<<"Sort took "<<chrono::duration_cast<chrono::microseconds>(Clock::now()-t1).count()<<" us\n";

    if(strat==1)
        FileManager::splitStrategy1_Vector(cont,*(vector<Student>*)nullptr,*(vector<Student>*)nullptr);
    else
        FileManager::splitStrategy2_Vector(cont,*(vector<Student>*)nullptr);
}

void runBatch(){
    vector<string> files = {"test_1000.txt","test_10000.txt","test_100000.txt"};
    for(int c=1;c<=3;c++)
        for(int s=1;s<=2;s++){
            cout<<"> C="<<c<<" S="<<s<<"\n";
            for(auto& f:files){
                try{ runOnce<vector<Student>>(s,f); }
                catch(...){ cout<<"err "<<f<<"\n"; }
            }
        }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(true){
        printMenu();
        switch(ask(1,4)){
            case 1:{
                int c = ask(1,3);
                int s = ask(1,2);
                runOnce<vector<Student>>(s,askFile());
                break;
            }
            case 2:
                runBatch();
                break;
            case 3:
                FileManager::generateTestFiles();
                break;
            case 4:
                return 0;
        }
    }
}
