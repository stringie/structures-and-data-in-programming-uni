#include "iostream"
#include "bintree.cpp"
using namespace std;

using tree = BinTree<int>;

int main(){
    tree t(0, tree(1, tree(2), tree(3)), tree(4, tree(5)));
    cout << t.isBOT();
}