#include <iostream>
#include "stack"
using namespace std;

stack<int> MergeStacks(stack<int> first, stack<int> second){
    int size = first.size() + second.size();
    stack<int> merged;
    for (int i = 0; i < size; ++i) {
        int firstTop = first.empty() ? INT32_MAX : first.top();
        int secondTop = second.empty() ? INT32_MAX : second.top();
        if(firstTop <= secondTop){
            merged.push(firstTop);
            first.pop();
        } else{
            merged.push(secondTop);
            second.pop();
        }
    }

    return merged;
}

int main() {

    stack<int> first({5, 3, 1});
    stack<int> second({6, 2, 1});

    stack<int> merged = MergeStacks(first, second);

    int size = merged.size();
    for (int i = 0; i < size; ++i) {
        cout << merged.top() << " ";
        merged.pop();
    }

}
