#include <iostream>
#include <limits>



using namespace std;

int func1(int* array, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += array[i];
    }
    return sum;
}

int func2(int array[], int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += array[i];
    }
    return sum;
}

int func(int &par){
    par = 1000;
    return par;
}

int main(){
    int a = 3;
    int &b = a;
    cout << &a << "\t" << &b << endl;
    cout << func(a) << a << b << endl;
}