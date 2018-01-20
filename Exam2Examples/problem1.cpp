#include "iostream"
#include "vector"
#include "stack"
using namespace std;

template <class T>
struct ListNode
{
    T data;
    ListNode<T>* next;
};

template <class T>
void remove(ListNode<T>*& node, T elem){    
    if(node == nullptr){
        return;
    }

    remove(node->next, elem);
    if (node->data == elem){
        node = node->next;
    }
}

// template <class T>
// int count(ListNode<T>* first, T elem){
//     if (first == nullptr){
//         return 0;                            // goes with commented removeDuplicates
//     }

//     if (first->data == elem){
//         return 1 + count(first->next, elem);
//     }else{
//         return count(first->next, elem);
//     }
// }

template <class T>
void removeDuplicates(ListNode<T>*& first){
    // if (first != nullptr){
    //     if(count(first, first->data) > 1){     // this is for removing all non-uniques
    //         remove(first, first->data);
    //         removeDuplicates(first);
    //     }else{
    //         removeDuplicates(first->next);
    //     }
    // }

    if (first == nullptr)
        return;
    removeDuplicates(first->next);              // for leaving leaving one of 'em
    remove(first->next, first->data);
}

template <class T>
void printNodes(ListNode<T>* first){
    if(first != nullptr){
        cout << first->data;
        printNodes(first->next);
    }
}

int main(){
    ListNode<int>* n = new ListNode<int>{2, new ListNode<int>{3, new ListNode<int>{2, new ListNode<int>{3, nullptr}}}};

    printNodes(n);    
    cout << endl;
    removeDuplicates(n);
    printNodes(n);
    
}