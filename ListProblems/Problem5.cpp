#include "iostream"
#include "list"
using namespace std;

template <typename T>
bool isPalindrome(list<T> word){
    for (auto it1 = word.begin(), it2 = word.end(); it1 != word.end() ;){
        if (*(it1++) != *(--it2)){
            return false;
        }
    }

    return true;
}

template <typename T>
bool isHigherOrderPalindrome(list<list<T>> words){
    list<T> word = words.front();
    words.pop_front();
    for (auto it1 = words.begin(); !words.empty();){
        list<T> next = words.front();
        words.pop_front();
        auto it = word.end();
        word.splice(it, next);
    }
    return isPalindrome(word);
}

int main(){
    list<char> az{'a','z'};
    list<char> obi4am{'o','b','i','4','a','m'};
    list<char> ma4{'m','a','4'};
    list<char> i{'i'};
    list<char> boza{'b','o','z','a'};
    list<list<char>> words{az, obi4am, ma4, i, boza};
    cout << isHigherOrderPalindrome(words);
}