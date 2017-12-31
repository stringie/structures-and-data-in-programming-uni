#ifndef __CALCULATOR_H_INCLUDED__
#define __CALCULATOR_H_INCLUDED__

#include "iostream"
#include "sstream"
#include "fstream"
using namespace std;

class Calculator
{
public:
    Calculator();
    ~Calculator();
    double getValue();
    Calculator& operator+(double num);
    Calculator& operator-(double num);
    Calculator& operator*(double num);
    Calculator& operator/(double num);
    string listOperations();
    Calculator& undo();
    Calculator& reset();
    void save(string filepath);
    void restore(string filepath);

private:
    double currentValue;
    // във pdf-а със условието на задачата не беше конкретно определено
    // какво трябва да се върне от операцията listOperations, затова си
    // позволих да използвам string който да пази формата на операциите
    // тъй като ми се стори най-удобно. Ако конкретно е трябвало някаква
    // структура вместо string, трябва да е по ясно изяснено. Списък може
    // означава всичко. Но не мисля че е проблем, функционално ще
    // постига същия ефект.
    string operations;
};

#include "Calculator.cpp"

#endif