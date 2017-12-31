#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Dwarf
{
    int i;
    Dwarf(int i_) : i(i_) {}
    vector<string> people;

    void assignToPerson(string person){
        people.push_back(person);
    }

    void printAssignedPeople(){
        for (auto person : people){
            cout << person << endl;
        }

        if (people.empty())
        {
            cout << "// няма рекламации" << endl;
        }
    }

    int fix(int time) {
        int fixed = 0;
        auto it = people.begin();
        while (it != people.end() && !people.empty())
        {
            if (i <= time){
                time -= i;
                fixed++;
                it = people.erase(it);
            } else {
                it++;
            }
        }

        return fixed;
    }
};

class NorthPole 
{
private:
    vector<Dwarf> dwarfs;
    int fixedPresents;
    bool fixAttempted;

public:
    
    NorthPole(int n)
    {
        for (int i = 1; i <= n; i++){
            Dwarf d(i);
            dwarfs.push_back(d);
        }
        fixedPresents = 0;
        fixAttempted = false;
    }

    void assignPresent(string person){
        int dwarf = person.back() - '0';
        person.pop_back();

        dwarfs[dwarf-1].assignToPerson(person);
    }

    void fixPresents(int time){
        auto it = dwarfs.begin();
        while (it != dwarfs.end())
        {
            int fixed = (*it).fix(time);
            fixedPresents += fixed;
            it++;
        }
        fixAttempted = true;
    }

    int fixed(int time){
        if (fixAttempted)
            return fixedPresents;
        fixPresents(time);
        return fixedPresents;
    }

    void printAssembly(){
        for (auto dwarf : dwarfs){
            cout << "Джудже " << dwarf.i << ':' << endl;
            dwarf.printAssignedPeople();
        }
    }
};


int main() {
    int n; cin >> n;
    NorthPole np(n);
    for (int i = 0; i < n; i++){
        string person; cin >> person;
        int dwarf; cin >> dwarf;
        np.assignPresent(person + to_string(dwarf));
    }
    int t; cin >> t;

    np.printAssembly();
    cout << "\n";
    cout << np.fixed(t) << endl;
    cout << "\n";
    np.printAssembly();

    int k; cin >> k;
}