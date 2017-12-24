#include "iostream"
#include "CircularList.h"
using namespace std;

int main(){
    int n, m; n = 1, m = 1;
    CircularList<int> c;
    for (int i = 0; i < n; i++){
        c.push_back(1);
    }

    int alive = n;
    for (auto it = c.begin(); alive != 1;){
        //how many alive people we pass must be m-1
        int passed = 0;
        //while we pass them and while we land on the next alive person
        for (int i = 0; passed < m-1 || *it != 1;){
            if(*it == 1){
                passed++;
            }
            it++;
        }
        //kill em
        *it = 0;
        alive--;
    }

    //find em
    int pos = 0;
    auto it = c.begin();
    while(*it != 1){
        it++;
        pos++;
    }

    cout << pos;
}