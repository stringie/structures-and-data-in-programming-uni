#include <iostream>

template <typename T>
struct Box
{
    T data;
    Box* next;

    Box(T _data, Box* _next);
};

template <typename T>
Box<T>::Box(T _data, Box<T>* _next) : data(_data), next(_next) {}

template <typename T>
void print(Box<T>* l){
    std::cout << "[";
    while(l != nullptr){
        const char* comma = l->next == nullptr ? "" : ", ";
        std::cout << l->data << comma;
        l = l->next;
    }
    std::cout << "]";
}

template <typename T>
int count(Box<T>* l, T x) {
    if (l == nullptr){
        return 0;
    }
    
    if (l->data == x){
        return 1 + count(l->next, x);
    }else{
        return count(l->next, x);
    }
}

template <typename T>
Box<int>* range(T x, T y){
    if (x <= y){
        Box<int>* first = new Box<int>(x, nullptr);
        Box<int>* current = first;
        
        while (x < y)
        {
            Box<int>* next = new Box<int>(++x, nullptr);
            current->next = next;
            current = next;
        }
        
        return first;
        
    }else{
        std::cout << "error";
    }
}

template <typename T>
void removeAll(Box<T>*& l, T x){
    while (l != nullptr && l->data == x)
    {
        Box<T>* tmp = l;
        l = l->next;
        delete tmp;
    }
    
    if(l != nullptr){
        removeAll(l->next, x);
    }
}

template <typename T>
void append(Box<T>*& l1, Box<T>*& l2){
    Box<T>* tmp = l1;
    while (tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    
    tmp->next = l2;
}

template <typename T>
Box<T>* concat(Box<T>* l1, Box<T>* l2){
    
    Box<T>* b = new Box<T>(l1->data, nullptr);
    append(b, l1->next);
    append(b, l2);
    return b;
}

template <typename T>
void map(T (*f)(T), Box<T>* l){
    Box<T>* current = l;
    while (current != nullptr)
    {
        current->data = f(current->data);
        current = current->next;
    }
}

template <typename T>
Box<T>* reverse(Box<T>* l){
    Box<T>* result = nullptr;

        while (l != nullptr)
        {
            Box<T>* tmp = result;
            result = new Box<T>(l->data, tmp);
            l = l->next;
        }
    
        return result;
}

template <typename T>
bool duplicates(Box<T>* l){
    while(l->next != nullptr){
        if(count(l, l->data) > 1){
            return true;
        }
        l = l->next;
    }
    return false;
}

template <typename T>
void removeDuplicates(Box<T>*& l){
    if(l == nullptr)
        return;
    if(duplicates(l)){
        if(count(l, l->data) > 1){
            removeAll(l->next, l->data);
        }
        removeDuplicates(l->next);
    }
}

template <typename T>
bool issorted(Box<T>* l){
    if(l->data > l->next->data){
        return issorted(reverse(l));
    }

    T prev = l->data;
    while (l->next != nullptr)
    {
        if(prev > l->next->data){
            return false;
        }
        prev = l->next->data;
        l = l->next;
    }

    return true;
}

template <typename T>
bool ispalindrome(Box<T>* l){
    Box<T>* rev = reverse(l);
    while(l != nullptr){
        if(rev->data != l->data){
            return false;
        }
        l = l->next;
        rev = rev->next;
    }

    return true;
}

void testRange(){
    print(range(1, 7));
}

void testConcat(){
    Box<int>* l1 = new Box<int>(1, 
                    new Box<int>(2,
                        new Box<int>(3, nullptr)));

    Box<int>* l2 = new Box<int>(15, 
                    new Box<int>(26,
                        new Box<int>(37, nullptr)));

    print(l1);
    print(l2);
    print(concat(l1, l2));
}

void testAppend(){

    Box<int>* l1 = new Box<int>(1, 
                    new Box<int>(2,
                        new Box<int>(3, nullptr)));

    Box<int>* l2 = new Box<int>(15, 
                    new Box<int>(26,
                        new Box<int>(37, nullptr)));

    print(l1);
    print(l2);
    append(l1, l2);
    print(l1);
}

void testMap(){

    Box<int>* l = new Box<int>(1, 
                    new Box<int>(2,
                        new Box<int>(3, nullptr)));
    
    print(l);
    map((int (*)(int))([](int x) -> int {return x*x;}), l);
    print(l);
}

void testCount(){

    Box<int>* l = new Box<int>(1, 
                    new Box<int>(1,
                        new Box<int>(3, nullptr)));
    print(l);
    std::cout << std::endl << count(l, 1) << " ones";
}

void testRemoveAll(){

    Box<int>* l = new Box<int>(1, 
                    new Box<int>(2,
                        new Box<int>(1, nullptr)));
    print(l);
    removeAll(l, 1);
    print(l);
}

void testReverse(){

    Box<int>* l = new Box<int>(1, 
                    new Box<int>(2,
                        new Box<int>(3, nullptr)));
    print(l);
    print(reverse(l));
}

void testDuplicates(){

    Box<int>* l = new Box<int>(1, 
                    new Box<int>(2,
                        new Box<int>(3, nullptr)));
    print(l);
    std::cout <<" " << duplicates(l) << std::endl;


    Box<int>* b = new Box<int>(1, 
                    new Box<int>(3,
                        new Box<int>(3, nullptr)));
    print(b);
    std::cout << " " << duplicates(b);
}

void testRemoveDuplicates(){
   
    Box<int>* l = new Box<int>(2, 
                    new Box<int>(3,
                        new Box<int>(3, 
                            new Box<int>(2, 
                                new Box<int>(3,
                                    new Box<int>(3, nullptr))))));

    print(l);
    removeDuplicates(l);
    print(l);
}

void testIssorted(){
    Box<int>* l = new Box<int>(6, 
                    new Box<int>(5,
                        new Box<int>(4, 
                            new Box<int>(3, 
                                new Box<int>(2,
                                    new Box<int>(1, nullptr))))));

    print(l);
    std::cout <<" "<< issorted(l) << std::endl;

    Box<int>* l2 = new Box<int>(1, 
                    new Box<int>(2,
                        new Box<int>(1, 
                            new Box<int>(4, 
                                new Box<int>(2,
                                    new Box<int>(6, nullptr))))));

    print(l2);
    std::cout << " " << issorted(l2);
}

void testIspalindrome(){
    Box<int>* l = new Box<int>(6, 
                    new Box<int>(5,
                        new Box<int>(4, 
                            new Box<int>(4, 
                                new Box<int>(5,
                                    new Box<int>(6, nullptr))))));

    print(l);
    std::cout << " " << ispalindrome(l);
}

int main(){
    
    //remove comment of a function to test it

//    testCount();
//    testRange();
//    testRemoveAll();
   testAppend();
//    testConcat();
//    testMap();
//    testReverse();
//    testDuplicates();
//    testRemoveDuplicates();
//    testIssorted();
//    testIspalindrome();

    return 0;
}