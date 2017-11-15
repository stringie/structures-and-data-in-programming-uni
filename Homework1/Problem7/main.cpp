#include <iostream>
#include <sstream>
#include <algorithm>
#include "stack"
using namespace std;

stack<char> CalculateSubExpr(stack<char> s) {
    string subExpr;

    while(s.top() != '('){
        subExpr += s.top();
        s.pop();
    }
    s.pop();

    int n = 0;
    int i = 1;
    while(!s.empty() && isdigit(s.top())){
        n += i * (s.top() - '0');
        i *= 10;
        s.pop();
    }

    reverse(subExpr.begin(), subExpr.end());
    for (int k = 0; k < n; ++k) {
        for (char j : subExpr) {
            s.push(j);
        }
    }

    return s;
}

string Calculate(string expr) {

    if(expr.find(')') == string::npos)
        return expr;

    istringstream iss(expr);
    stack<char> s;

    char c;
    while(iss >> c){
        if (c == ')'){
            s = CalculateSubExpr(s);
        }else{
            s.push(c);
        }
    }

    string res;
    while (!s.empty()){
        res += s.top();
        s.pop();
    }

    return res;
}

int main() {

    string expression = "2(2(ab))";
    string result = Calculate(expression);

    reverse(result.begin(), result.end());
    cout << result;
}