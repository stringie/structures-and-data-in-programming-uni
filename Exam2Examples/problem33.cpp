#include "iostream"
#include "vector"
using namespace std;

struct Elem
{
    int x;
    Elem* next;  
};

void combineSum(vector<Elem*> lists, int n, Elem*& L){
    int i = 1;
    while (true)
    {
        int sum = 0;
        for (int j = 0; j < n; j++){
            Elem* curr = lists[j];
            int currIndex = 1;
            while (curr != nullptr){
                if (currIndex == i){
                    sum += curr->x;
                    break;
                }
                curr = curr->next;
                currIndex++;
            }
        }

        if (sum == 0){
            break;
        }else{
            if(i == 1){
                L = new Elem{sum, nullptr};
            }else{
                Elem* tmp = L;
                while (tmp->next != nullptr){
                    tmp = tmp->next;
                }
                tmp->next = new Elem{sum, nullptr};
            }
            i++;
        }
    }
}

int main(){
    vector<Elem*> ls{new Elem{1, new Elem{2, new Elem{3, new Elem{4, nullptr}}}}, new Elem{5, new Elem{6, nullptr}}, new Elem{7, nullptr}};
    Elem* l = new Elem{1, nullptr};
    combineSum(ls, 3, l);

    while (l != nullptr){
        cout << l->x << " ";
        l = l->next;
    }
}