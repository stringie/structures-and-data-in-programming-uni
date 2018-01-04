#include "iostream"
#include "bintree.cpp"
using namespace std;

using tree = BinTree<int>;


BinTree<int> replaceNodesWithCount(BinTreePosition<int> pos){
    if (!pos.valid()){
        return BinTree<int>();
    }

    BinTree<int> left = replaceNodesWithCount(pos.left());
    BinTree<int> right = replaceNodesWithCount(pos.right());

    int r1 = 0;
    if(left.rootpos().valid())
        r1 = left.root();
    
    int r2 = 0;
    if(right.rootpos().valid()){
        r2 = right.root();
    }

    return BinTree<int>(1 + r1 + r2, left, right);
}

int main(){
    tree t(7, tree(2, tree(1)), tree(4, tree(1), tree(2, tree(1))));
    tree replaced = replaceNodesWithCount(t.rootpos());
    replaced.printDOT();
}