#include<queue>
#include<iostream>

using namespace std;


class A{
public:
    virtual void print(){
        cout << "this is class A" << endl;
    }
};

class B: public A{
public:
    void print(){
        cout << "this is class B" << endl;
    }
};

class C: public A{
public:
    void print(){
        cout << "this is class C" << endl;
        A::print();
    }
};

int main(){
    A* a = new A();
    B b;
    C c;
    a->print();
    a = &b;
    a->print();
    a = &c;
    a->print();
}