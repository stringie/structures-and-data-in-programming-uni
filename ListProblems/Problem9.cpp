#include "iostream"
#include "algorithm" //for reverse .... seriously c++
#include "CircularList.h"
using namespace std;

bool isPalindrome(string s){
    string copy = s;
    reverse(copy.begin(), copy.end());

    return copy == s;
}

string checkForPalindrome(CircularList<char> c){
    for (int i = 0; i < c.size(); i++){
        auto it = c.begin();
        for (int j = 0; j < i; j++){
            it++;
        }

        string check = "";
        for (int j = 0; j < c.size(); j++){
            check += *it;
            it++;
        }

        if (isPalindrome(check)){
            return check;
        }
    }
}

int main(){
    string s = "robborrowor";
    CircularList<char> c;
    for (auto chr : s){
        c.push_back(chr);
    }

    cout << checkForPalindrome(c);
}