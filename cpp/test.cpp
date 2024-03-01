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

vector<string> func(){
    
}

int main(){
    while (1)
    {
        cout<<"firstloop"<<endl;
        if(1) break;
    }
    return 0;
}