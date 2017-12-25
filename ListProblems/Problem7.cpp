#include "iostream"
#include "CircularList.h"
#include "queue"
using namespace std;

string decipher(CircularList<char> c, queue<int> q){
    string deciphered = "";
    auto it = c.begin();
    while(!q.empty()){
        int pos = q.front();
        q.pop();

        //for not dealing with a doubly linked circular list i can only go forward
        //negated is for when i have to go back by one since erasing leaves the iterator in different
        //positions in a doubly linked list
        bool negated = false;
        if (pos < 0){
            pos += c.size();
            negated = true;
        }
        
        for (int i = 0; i < pos; i++){
            ++it;
        }

        char element = *it;

        it = c.erase(it);
        if(negated){
            for (int i = 0; i < c.size()-1; i++){
                it++;
            }
        }
        deciphered += element;
    }

    return deciphered;
}

int main(){
    string cipher = "abcdefghijklmnopqrstuvwxyz";
    queue<int> q({8,4,-2,10,4,-5,4,-6,2});
    CircularList<char> c;
    for (auto chr : cipher){
        c.push_back(chr);
    }

    cout << decipher(c, q);
}