# include<iostream>
# include<queue>

using namespace std;

class test{
public:
    static void get(){
        int a = 1;
        cout << "now the val of a is " << a << endl;
        a++;
    }

    void display(){
        cout << "this is display function" << endl;
    }
};

static int count(){
    static int a = 1;
    a++;
    return a;
}


class cmp{
public:
    bool operator()(int b, int a){
        return a < b;
    }
};

int ttt(){
    cout <<"this" << endl;
    return 100;
}

void add(){
   cout << "函数被调用" << endl;
}
int main(){
   // 输出函数add的地址
   cout << ttt << endl;
   // 对add取地址
   cout << &add << endl;
   // 对函数名取内容
   cout << *add << endl;//这样规定，所以才会得到地址
   // 结果是一样的地址，但是返回类型不同
   cout << typeid(add).name() << endl;
   cout << typeid(&add).name() << endl;
   cout << typeid(*add).name() << endl;
}