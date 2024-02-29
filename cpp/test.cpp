#include <iostream>
#include <limits>
#include<vector>



using namespace std;

void text(){
    vector<int> it;
    for(int i = 0; i < 100; i++){
        it.push_back(i);
    }
    // 第一种遍历方法
    for(vector<int>:: iterator i = it.begin(); i < it.end(); i++){
        cout << *i << endl;
    }
}

int main(){
    vector<int> a({1, 2,3,4});
    for(int i = 0; i <4; i++){
        cout<<a[i];
    }
}