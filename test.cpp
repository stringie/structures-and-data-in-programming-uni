#include "iostream"
#include "list"
#include "fstream"
#include "string.h"
using namespace std;

class Taxi {
public:
    Taxi(char name[50], double r) {
        strcpy(company, name);
        rate = r;
    }

private:
    char company[50];
    double rate;

    // friend istream& operator>>(istream& is, const Taxi& t){
    //     char c[50];
    //     is >> c;
    //     double r;
    //     is >> r;

    //     t.company = c;
    //     t.rate = r;
    // }

    friend ostream& operator<<(ostream& os, const Taxi& t){
        cout << "company: " << t.company << " rate: " << t.rate;
    }
};


int main(){
    Taxi t("Made up company", 20.2);
    cout << t;
}