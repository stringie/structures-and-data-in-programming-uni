#include "iostream"
#include "list"
#include "string"
using namespace std;

string decipher(list<char> cipher){
    string deciphered = "";
    auto decipherer = cipher.begin();
    int first = true;
    for(auto it = cipher.begin(); it != cipher.end();){
        int step = *it - '0';
        if (first){step--;}
        if(step < 10){
            advance(decipherer, step);
            deciphered += *decipherer;
            it = cipher.erase(it);
            first = false;
            continue;
        }
        it++;
    }

    return deciphered;
}

int main(){
    string cipher = "abcd2ef3ghi1jklm3nop5qrs4tuv4wxy11z";
    list<char> l;
    for (auto c : cipher){
        l.push_back(c);
    }
    cout << decipher(l);
}