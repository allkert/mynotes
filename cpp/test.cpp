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

int main(){
    int a = 3;
    int &b = a;
    int &c = b;
    c++;
    cout << a << b << c << endl;
}