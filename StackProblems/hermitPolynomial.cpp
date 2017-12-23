#include <iostream>
#include <stack>
using namespace std;


int main() {
    stack<double> s;
    int n; double x; cin >> n >> x;

    for (int i = 0; i <= n; ++i) {
        if (i == 0){
            s.push(1);
        } else if (i == 1){
            s.push(2*x);
        } else{
            double minusOne = s.top();
            s.pop();
            double minusTwo = s.top();
            double current = 2 * x * minusOne + 2 * (i - 1) * minusTwo;
            s.push(minusOne);
            s.push(current);
        }
    }

    cout << s.top();
}