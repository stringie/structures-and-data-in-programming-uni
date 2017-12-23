#include "iostream"
#include "list"
using namespace std;

int main(){
    int n; n = 9;
    list<int> c;
    for (int i = 1; i <= n; i++){
        c.push_back(i);
        c.push_back(i);
    }

    for (auto i : c) {
        cout << i << " ";
    }
    cout << '\n';
 
    auto it = c.begin();
    it++;

    int index = 1;
    int e;
    while (index < c.size()){
        e = *it;
        it = c.erase(it);
        advance(it, e-1);
        index += e-1;
    }
 
    for (auto i : c) {
        cout << i << " ";
    }
    cout << '\n';
}