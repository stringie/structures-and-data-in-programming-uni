#include <iostream>
#include <queue>

using namespace std;

int GetPthElement(queue<int> q, int p){
    int count = 1;
    while (true){
        q.push(q.front() + 1);
        count++;
        if(count == p){
            return q.back();
        }
        q.push(q.front() * 2);
        count++;
        if(count == p){
            return q.back();
        }

        q.pop();
    }
}

int main() {

    int n, p; cin >> n >> p;
    queue<int> q;
    q.push(n);

    int pth = GetPthElement(q, p);

    cout << pth;
}