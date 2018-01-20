#include "iostream"
#include "stack"
#include "vector"
using namespace std;

template <typename T>
struct TreeNode{
    T data;
    vector<TreeNode*> children;
};

template <typename T>
void printLeaves(const TreeNode<T>* root){
    if (root == nullptr)
        return;

    stack<const TreeNode<T>*> s;
    s.push(root);
    while (!s.empty()){
        const TreeNode<T>* top = s.top();
        s.pop();
        if(top->children.size() == 0){
            cout << top->data << " ";
        }else{
            for (int i = top->children.size() - 1; i >= 0; i--)
            {
                s.push(top->children[i]);
            }
        }
    }
}


int main(){
    
    vector<TreeNode<int>*> childChildren{new TreeNode<int>{4, vector<TreeNode<int>*>()}, new TreeNode<int>{5, vector<TreeNode<int>*>()}};
    vector<TreeNode<int>*> rootChildren{new TreeNode<int>{9, vector<TreeNode<int>*>()}, new TreeNode<int>{2, childChildren}, new TreeNode<int>{3, vector<TreeNode<int>*>()}};
    TreeNode<int>* r = new TreeNode<int>{1, rootChildren};

    printLeaves(r);
}