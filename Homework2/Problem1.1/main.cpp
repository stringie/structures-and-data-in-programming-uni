#include <iostream>
#include "stack"

using namespace std;

int Factorial(int n){
    stack<int> s;
    s.push(1);

    for (int i = 1; i <= n; ++i) {
        s.push(s.top()*i);
    }

    return s.top();
}

int main(){

    int n; cin >> n;
    int factorial = Factorial(n);

    cout << factorial;
}