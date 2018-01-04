#include "iostream"
#include "bintree.cpp"
#include "vector"
#include "set"
using namespace std;

using tree = BinTree<int>;

bool hasPairSameSetLevels(tree t){
    vector<set<int>> levels;
    int d = depth(t.rootpos());
    for (int i = 1; i <= d; i++){
        vector<int> v = t.level(i);
        set<int> s(v.begin(), v.end());

        levels.push_back(s);
    }

    int sameSets = 0;
    for (auto l1 : levels){
        for (auto l2 : levels){
            if (l1 == l2){
                sameSets++;
            }
        }
    }

    return sameSets > d;
}

int main(){
    tree t(0, tree(1, tree(1), tree(4)), tree(4, tree(1)));
    cout << hasPairSameSetLevels(t);
}