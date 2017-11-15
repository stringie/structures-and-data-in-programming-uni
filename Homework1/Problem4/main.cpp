#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

int Calculate(string expression);

stack<char> CalculateSubExpr(stack<char> s);

int toDigit(char &top);

char toChar(int i);

int main() {
    string expr = "((2 @ (1 $ (2 @ 9))) @ ((8 @ 8) $ 4))";
    int result = Calculate(expr);

    cout << result;
}

int Calculate(string expression) {
    if (expression.size() == 1)
        return expression[0] - '0';

    stack<char> s;
    istringstream expr(expression);
    char c;
    while (expr >> c){
        if(c == ')'){
           s = CalculateSubExpr(s);
        } else{
            s.push(c);
        }
    }

    return toDigit(s.top());
}

stack<char> CalculateSubExpr(stack<char> s){
    int rarg = toDigit(s.top());
    s.pop();
    char op = s.top();
    s.pop();
    int larg = toDigit(s.top());
    s.pop();
    s.pop(); // pop the '('

    if(op == '$'){
        char min = toChar(larg <= rarg ? larg : rarg);
        s.push(min);
    } else{
        char add = toChar((larg + rarg) % 10);
        s.push(add);
    }

    return s;
}

char toChar(int i) {
    return '0' + i;
}

int toDigit(char &top) {
    return top - '0';
}