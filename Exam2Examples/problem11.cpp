#include "iostream"
using namespace std;

struct Node{
    int x;
    Node* left;
    Node* right;  
};

bool complement(const Node* t1, const Node* t2){
    if(t1 == nullptr && t2 != nullptr){
        return false;
    }

    if (t2 == nullptr){
        return true;
    }

    if (t1->x == t2->x && complement(t1->left, t2->left) && complement(t1->right, t2->right)){
        return true;
    }

    return false;
}

int main(){
    Node* n1 = new Node{1, new Node{2, nullptr, nullptr}, new Node{3, nullptr, new Node{4, nullptr, nullptr}}};
    Node* n2 = new Node{1, new Node{2, nullptr, nullptr}, nullptr};

    cout << complement(n1, n2);
}