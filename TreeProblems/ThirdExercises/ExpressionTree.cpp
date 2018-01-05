#include "iostream"
#include "bintree.cpp"
#include "sstream"
using namespace std;

BinTree<char> createExprTree(istringstream& iss){
    char c;
    iss >> c;
    if (isdigit(c)){
        return BinTree<char>(c);
    }

    BinTree<char> leftTree = createExprTree(iss);
    iss >> c;
    BinTree<char> rightTree = createExprTree(iss);

    iss.get();
    return BinTree<char>(c, leftTree, rightTree);
}

int main(){
    string expr = "((1*4)+2)";
    istringstream iss(expr);
    BinTree<char> tree = createExprTree(iss);
    tree.printDOT();
}