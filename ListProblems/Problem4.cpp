#include <cmath>
#include "iostream"
#include "list"
using namespace std;

class Monomial{
    double coeff;
    double power;

public:
    Monomial(double c, double p){
        coeff = c;
        power = p;
    }

    double getCoeff(){ return coeff;}
    double getPower(){ return power;}

    double eval(double x){
        return coeff * pow(x, power);
    }

    Monomial* multiply(Monomial* m){
        coeff *= m->getCoeff();
        power += m->getPower();

        return this;
    }

    void print(){
        cout << coeff << "*x^" << power;
    }
};

class Polynomial{
private:
    list<Monomial*> polynomial;
public:

    Polynomial() = default;

    explicit Polynomial(Monomial* m){
        add(m);
    }

    list<Monomial*> getPolynomial(){
        return polynomial;
    }

    Polynomial* add(Monomial* m){
        polynomial.push_back(m);
        return this;
    }

    double eval(double x){
        double y = 0.0;
        for (Monomial* m : polynomial){
            y += m->eval(x);
        }
        return y;
    }

    Polynomial* sumTwoPolynomials(Polynomial* p){
        for (Monomial* m : p->getPolynomial()){
            add(m);
        }
        return this;
    }

    Polynomial* productMonomial(Monomial* m){
        for (Monomial* mono : polynomial){
            mono->multiply(m);
        }
        return this;
    }

    Polynomial* productPolynomial(Polynomial* p){
        list<Monomial*> currentPolynomial = getPolynomial();
        while (!polynomial.empty())
            polynomial.pop_front();
        for (Monomial* m1 : p->getPolynomial()){
            for (Monomial* m2 : currentPolynomial){
                Monomial* m = new Monomial(m2->getCoeff(), m2->getPower());
                m->multiply(m1);
                add(m);
            }
        }

        return this;
    }

    void print(){
        for (Monomial* m : polynomial){
            m->print();
            cout << " + ";
        }
        cout << "0\n";
    }
};


int main(){
    Monomial* m1 = new Monomial(1,1);
    Monomial* m2 = new Monomial(1,2);
    Monomial* m3 = new Monomial(2,3);
    Polynomial* p1 = new Polynomial(m1);
    p1->add(m2);
    Polynomial* p2 = new Polynomial(m3);
    p2->add(m2);
    p1->sumTwoPolynomials(p2)->productMonomial(m1)->productPolynomial(p2)->print();
    cout << p1->eval(2);
}