#include "iostream"
using namespace std;

const int N = 6;

bool a[N][N] = {                
    1, 1, 0, 0, 1, 1,           
    0, 1, 0, 1, 0, 1,           
    1, 1, 0, 0, 1, 1,           
    1, 1, 0, 0, 1, 0,           
    1, 0, 1, 0, 1, 1,           
    0, 0, 0, 0, 0, 0,          
};                              

bool hasLadder(int start, int k){
    if (k == 0){
        return true;
    }

    for (int i = 0; i < N; i++){
        if (i > start && a[start][i] == 1 && hasLadder(i, k-1)){
            return true;
        }
    }

    return false;
}

int main(){
    cout << hasLadder(0, 4);
}