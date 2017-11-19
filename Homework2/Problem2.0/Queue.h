//
// Created by string on 11/15/17.
//

#ifndef PROBLEM2_0_QUEUE_H
#define PROBLEM2_0_QUEUE_H

#include <iostream>
#include "stack"
using namespace std;

template <typename T>
class Queue {

private:
    stack<T> inbox;
    stack<T> outbox;
    int size = 0;
public:
    Queue<T>();
    void enqueue(T in);
    void print();
    bool hasUniqueElements();
    int getElementCount(T e, Queue<T> q);
    void Reverse();
    void printAscending();
    T dequeue();
    int Size();
    bool Empty();
};


#endif //PROBLEM2_0_QUEUE_H
