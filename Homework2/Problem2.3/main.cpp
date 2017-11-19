#include <iostream>
#include "queue"
using namespace std;


void PrintABIntervals(int a, int b, int arr[]);

int main() {

    int a, b; cin >> a >> b;
    int array[] = {6, 8, 1, 3, 5, 9, 2, 4, 7};

    PrintABIntervals(a, b, array);    
}

void PrintABIntervals(int a, int b, int arr[]) {
    int size = 9;
    queue<int> q;
    for (int j = 0; j < size; ++j) {
        int x = arr[j];
        if(x < a){
            cout << x << " ";
        } else {
            q.push(x);
        }
    }

    bool firstOcc = true;
    while (!q.empty()){
        if(q.front() <= b){
            cout << q.front() << " ";
            q.pop();
        }
        else {
            if(firstOcc){
                firstOcc = false;
                q.push(INT32_MAX);
            }
            int other = q.front();
            q.pop();
            q.push(other);
        }

        if(q.front() == INT32_MAX){
            q.pop();
            while(!q.empty()){
                cout << q.front() << " ";
                q.pop();
            }
        }
    }
}