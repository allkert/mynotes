#include<queue>
#include<iostream>

using namespace std;

int main(){
    priority_queue<int> a;
    a.push(4);
    a.push(5);
    a.push(3);
    cout << a.top();
}