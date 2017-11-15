#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;

string Calculate(string expression);

int main() {
    string expr = "abcd*efg****hij*klm";
    string result = Calculate(expr);

    cout << result;
}

string Calculate(string expression) {
    stack<char> s;
    istringstream expr(expression);
    char c;
    while (expr >> c){

        if(c == '*'){
            s.pop();
        } else if (c == '-'){
            s = stack<char>();
        }else{
            s.push(c);
        }
    }

    string result;
    int size = s.size();
    for (int i = 0; i < size; ++i) {
        result += s.top();
        s.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}