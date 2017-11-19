//
// Created by string on 11/15/17.
//

#include <algorithm>
#include "Queue.h"
#include "vector"

template <typename T>
Queue<T>::Queue() {}

template <typename T>
void Queue<T>::enqueue(T in) {
    inbox.push(in);
    size++;
}

template <typename T>
T Queue<T>::dequeue() {
    if(outbox.empty()){
        while (!inbox.empty()){
            outbox.push(inbox.top());
            inbox.pop();
        }
    }

    T out = outbox.top();
    outbox.pop();
    size--;
    return out;
}

template <typename T>
bool Queue<T>::hasUniqueElements() {
    for (int i = 0; i < Size(); ++i) {
        T top = this->dequeue();
        if(this->getElementCount(top, *this) > 0){
            return false;
        }
        this->enqueue(top);
    }

    return true;
}

template <typename T>
int Queue<T>::getElementCount(T e, Queue<T> q) {
    int count = 0;
    int size = q.Size();
    for (int i = 0; i < size; ++i) {
        T top = q.dequeue();
        if (top == e){
            count++;
        }
    }

    return count;
}

template <typename T>
void Queue<T>::Reverse() {
    stack<T> s;
    int size = Size();
    for (int i = 0; i < size; ++i) {
        s.push(this->dequeue());
    }

    while (!s.empty()){
        this->enqueue(s.top());
        s.pop();
    }
}

template <typename T>
void Queue<T>::printAscending() {
    int size = Size();
    vector<int> v;
    for (int i = 0; i <size; ++i) {
        int curr = dequeue();
        v.push_back(curr);
        enqueue(curr);
    }

    sort(v.begin(), v.end());
    for(int i : v){
        cout << i << " ";
    }
}

template <typename T>
void Queue<T>::print() {
    int size = Size();
    for (int i = 0; i < size; ++i) {
        T top = dequeue();
        cout << top << " ";
        enqueue(top);
    }
}

template <typename T>
int Queue<T>::Size() {
    return size;
}

template <typename T>
bool Queue<T>::Empty() {
    return size == 0;
}