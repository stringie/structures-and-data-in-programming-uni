#include "iostream"
#include "vector"
using namespace std;

vector<pair<char,int>> getCharFrequency(string s){
    vector<pair<char,int>> frequency;
    auto sit = s.begin();
    while (sit != s.end()){
        bool present = false;
        auto fit = frequency.begin();
        while (!present && fit != frequency.end()){
            if ((*fit).first == (*sit)){
                present = true;
                (*fit).second++;
            }

            fit++;
        }

        if (!present){
            auto p = make_pair((*sit), 1);
            frequency.push_back(p);
        }
        sit++;
    }

    return frequency;
}

int main(){
    string test = "This is a random string of character to test coding";
    vector<pair<char, int>> charFrequency = getCharFrequency(test);

    for (auto p : charFrequency){
        cout << "char: " << p.first << " count: " << p.second << endl;
    }
}