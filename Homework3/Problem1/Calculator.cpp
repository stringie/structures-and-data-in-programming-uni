#include "Calculator.h"

Calculator::Calculator() : currentValue(0), operations("") {}

Calculator::~Calculator() {}

double Calculator::getValue(){
    return currentValue;
}

string Calculator::listOperations(){
    return operations;
}

Calculator& Calculator::operator+(double num){
    currentValue += num;
    ostringstream strs;
    strs << num;
    operations += '+' + strs.str();
    return *this;
}

Calculator& Calculator::operator-(double num){
    currentValue -= num;
    ostringstream strs;
    strs << num;
    operations += '-' + strs.str();
    return *this;
}

Calculator& Calculator::operator*(double num){
    currentValue *= num;
    ostringstream strs;
    strs << num;
    operations += '*' + strs.str();
    return *this;
}

Calculator& Calculator::operator/(double num){
    currentValue /= num;
    ostringstream strs;
    strs << num;
    operations += '/' + strs.str();
    return *this;
}

Calculator& Calculator::undo(){
    if (operations != "")
    {
        char num = operations.back();
        int number = num - '0';
        operations.pop_back();
        char op = operations.back();
        operations.pop_back();

        switch (op)
        {
            case '+': currentValue-=number; break;
            case '-': currentValue+=number; break;
            case '*': currentValue/=number; break;
            case '/': currentValue*=number; break;
        }
    }
}

Calculator& Calculator::reset(){
    currentValue = 0;
    operations = "";    
    return *this;
}

void Calculator::save(string filepath){
    ofstream file(filepath);
    if (!file){
        cerr << "error writing";
    } else {
        file << operations;
    }    
}

void Calculator::restore(string filepath){
    ifstream file(filepath);
    if (!file)
    {
        cerr << "error reading";
    } else {
        reset();
        string ops;
        getline(file, ops);
        stringstream ss(ops);
        while (!ss.eof())
        {
            char op; ss >> op;
            double num; ss >> num;
            switch (op)
            {
                case '+': (*this)+num; break;
                case '-': (*this)-num; break;
                case '*': (*this)*num; break;
                case '/': (*this)/num; break;
            }
        }        
    }
}