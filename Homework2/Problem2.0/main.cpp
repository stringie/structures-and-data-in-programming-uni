#include <iostream>
#include "Queue.h"
#include "Queue.cpp"
using namespace std;

int main() {

    Queue<int> q;
    q.enqueue(1);
    q.enqueue(9);
    q.enqueue(4);

    q.Reverse();
    cout << q.hasUniqueElements() << endl;
    q.enqueue(4);
    cout << q.hasUniqueElements() << endl;
    q.print();
    cout << endl;
    q.printAscending();

}