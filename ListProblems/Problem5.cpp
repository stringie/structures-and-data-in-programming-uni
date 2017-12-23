#include "iostream"
#include "list"
using namespace std;

template <typename T>
bool isPalindrome(list<T> l){
    list<T> copy = l;
    copy.reverse();

    for (auto it1 = l.begin(), it2 = copy.begin(); it1 != l.end() ;){
        if (*(it1++) != *(it2++)){
            return false;
        }
    }

    return true;
}

int main(){
    list<char> l{'n','e','r','v','e','n'};
    cout << isPalindrome(l);
}