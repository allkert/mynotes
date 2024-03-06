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
   cout << "����������" << endl;
}
int main(){
   // �������add�ĵ�ַ
   cout << ttt << endl;
   // ��addȡ��ַ
   cout << &add << endl;
   // �Ժ�����ȡ����
   cout << *add << endl;//�����涨�����ԲŻ�õ����?
   // �����һ���ĵ�ַ�����Ƿ������Ͳ��?
   cout << typeid(add).name() << endl;
   cout << typeid(&add).name() << endl;
   cout << typeid(*add).name() << endl;
}