[TOC]
# cpp 面向对象

## 面向对象

类是一种用户自定义的数据类型。类中的数据称为**成员变量**，类中的函数称为**成员函数**。

### 1. 类的基本知识

#### 1.1 类的声明

```cpp
class Box
{
   public:
      double length;   // 长度
      double breadth;  // 宽度
      double height;   // 高度
      double get(void);
};
double Box::get(void)
{
    return length * breadth * height;
}
//也可以直接把函数定义在类中，这样就不需要再单独定义函数了。
```

#### 1.2 类成员函数

类成员函数有两种声明方式：

- 在类定义中声明
- 在类定义外定义

#### 1.3 类的访问控制

- public：类的外部代码可以访问类的公有成员
- private：类的外部代码不能访问类的私有成员

  一般情况下只有类的**成员函数**可以访问类的私有成员，但是**友元函数**也可以访问类的私有成员
- protected：类的外部代码不能访问类的保护成员，它与 private 的区别是，protected 成员可以在派生类（子类）中访问。

默认的访问修饰符是 private，即如果不写访问修饰符，默认是 private。

#### 1.4 构造函数 and 析构函数

- 构造函数：类的构造函数是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。构造函数可用于为某些成员变量设置初始值。
- 析构函数：类的析构函数是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行。析构函数的名称与类的名称是完全相同的，只是在名称前面加上了一个波浪号（~）。析构函数不返回任何值，也不能带有任何参数。析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。

**析构函数在以下情况下会被调用：**

1. 对象在程序结束时被销毁
2. 对象超出作用域时被销毁，例如函数执行完毕时
3. delete 一个对象时被销毁
4. 一个对象被另一个对象替代时被销毁

##### 1.4.1 拷贝构造函数

拷贝构造函数是一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象。拷贝构造函数通常用于：

- 通过使用另一个同类型的对象来初始化新创建的对象。
- 复制对象把它作为参数传递给函数。
- 复制对象，并从函数返回这个对象。

**拷贝构造函数在以下几种情况下会被调用：**

1. 使用一个对象初始化另一个对象
2. 如果函数的形参是类的对象，调用此函数的时候，进行形参和实参相结合时，复制构造函数被调用

**这里要注意，类的对象作为函数的参数是属于值传递，并不会改变原来的对象。**

1. 函数的返回值，如果函数的返回值是类的一个对象，函数执行完成返回调用者时，复制构造函数被调用

```cpp
"类名 (const \"类名\" &obj) {
   // 构造函数的主体
}
"
# include<iostream>

using namespace std;

class Line{
public:
    Line(int len){
        cout << "调用构造函数" << endl;
        ptr = new int;
        *ptr = len;
    }

    Line(const Line &obj){
        cout << "调用拷贝构造函数" << endl;
        ptr = new int;
        *ptr = *obj.ptr;
    }

    ~Line(){
        cout << "调用析构函数， 释放内存" << endl;
        delete ptr;
    }

    int getLength(){
        return *ptr;
    }

private:
    int *ptr;
};

void display(Line obj){
    cout << "line 大小：" << obj.getLength() << endl;
}

int main(){
    Line line1(10);
    Line line2 = line1;// 将一个对象复制到另一个对象，调用了拷贝构造函数

    // 作为参数传入函数时调用拷贝构造函数
    // 这里实质也是一个复制，所以也会调用拷贝构造函数
    display(line1);
    display(line2);
}
```

#### 1.5 友元函数

类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。**友元函数不是成员函数**，但是它可以访问类中的私有成员。使用关键词 `friend` 来声明友元函数。

```cpp
class Box
{
   double width;
public:
   double length;
// 友元函数
   friend void printWidth( Box box );
// 如果要把一个类的成员函数作为友元函数，只需要在类的定义中声明该函数
   friend class BigBox;
   void setWidth( double wid );
};
```

#### 1.6 内联函数

- 内联函数的作用是：在编译时将函数调用直接展开为函数体代码，而不是通过函数调用的方式进行调用。内联函数可以提高程序的运行速度，但是会增加程序的体积。
- 内联函数通常与类一起使用，在编译时，编译器会把该函数的代码插入到每个调用该函数的地方。
- 对内联函数进行修改，需要重新编译整个程序，因为编译器需要重新替换所有的函数调用。
- 使用关键字 `inline` 来声明内联函数。
- 内联函数通常为简单的函数，如果定义的函数超过 1 行，编译器会忽略内联请求。
- 在类定义中定义的函数默认是内联函数。

#### 1.7 this 指针

this 指针是所有成员函数的隐含参数。在成员函数内部，this 指针指向调用该成员函数的对象。

注意！！！！：友元函数不是当前类的成员函数，所以友元函数没有 this 指针。

#### 1.8 指向类的指针

`MyClass *ptr = new MyClass;`

该指针不能访问类的私有成员和保护成员，但是可以通过公有成员函数访问私有成员和保护成员。

#### 1.9 类的静态成员

`static`

静态成员是在类的所有对象中是共享的。无论类的对象有多少个，静态成员只有一个副本。静态成员在类的所有对象中是共享的，可以在不创建类的对象的情况下访问静态成员。

1. 静态变量
2. 静态函数

- 静态函数不可以使用 this 指针，因为静态函数不是对象的成员函数，所以不能访问非静态成员。
- 静态成员函数只能访问静态成员变量和静态成员函数。以及类外部的其他函数和变量。
- 静态函数内部的定义的变量不是静态的，是局部变量，只能在函数内部使用，除非定义为静态变量。

### 2. 重载运算符和重载函数

重载的作用是：使得函数名可以根据参数的不同而有不同的功能。

c++ 允许在同一作用域中的某个函数和运算符指定多个定义，分别称为函数重载和运算符重载。

当您调用一个重载函数或重载运算符时，编译器通过把您所使用的参数类型与定义中的参数类型进行比较，决定选用最合适的定义。选择最合适的重载函数或重载运算符的过程，称为重载决策。

#### 2.1 函数重载

函数重载是指在同一个作用域中，可以定义多个功能类似的同名函数，但是这些同名函数的参数列表（参数的个数或参数的类型）必须不同。

```cpp
class printData
{
   public:
      void print(int i) {
        cout << "整数为: " << i << endl;
      }
      void print(double  f) {
        cout << "浮点数为: " << f << endl;
      }
      void print(char c[]) {
        cout << "字符串为: " << c << endl;
      }
};
```

#### 2.2 运算符重载

运算符重载是指重新定义运算符的功能。c++ 允许在类中重载大部分运算符。

重载的运算符是带有特殊名称的函数，函数名是由关键字 operator 和其后要重载的运算符符号构成的。

```cpp
class Box
{
   public:
      double getVolume(void)
      {
         return length * breadth * height;
      }
      void setLength( double len )
      {
          length = len;
      }
      void setBreadth( double bre )
      {
          breadth = bre;
      }
      void setHeight( double hei )
      {
          height = hei;
      }
      // 重载 + 运算符，用于把两个 Box 对象相加
      Box operator+(const Box& b)
      {
         Box box;
         box.length = this->length + b.length;
         box.breadth = this->breadth + b.breadth;
         box.height = this->height + b.height;
         return box;
      }
   private:
      double length;      // 长度
      double breadth;     // 宽度
      double height;      // 高度
};
```

可以重载的运算符有：

| 运算符         | 描述                                                                     |
| -------------- | ------------------------------------------------------------------------ |
| 双目算术运算符 | + (加)，- (减)，* (乘)，/ (除)，% (取模)                                 |
| 关系运算符     | == (等于)，!= (不等于)，> (大于)，< (小于)，>= (大于等于)，<= (小于等于) |
| 逻辑运算符     | && (逻辑与)，                                                            |
| 单目运算符     | + (正)，- (负)，*(指针)，& (取地址)                                      |
| 自增自减运算符 | ++ (自增)，-- (自减)                                                     |
| 位运算符       | & (按位与)，                                                             |
| 赋值运算符     | =, +=, -=, *=, /=, %=, &=,                                               |
| 空间申请与释放 | new, delete, new[] , delete[]                                            |
| 其他运算符     | () (函数调用)，-> (通过指针访问成员)，, (逗号)，[] (下标)                |

不可以重载的运算符有：

| 运算符 | 描述               |
| ------ | ------------------ |
| .      | 成员访问运算符     |
| .*     | 成员指针访问运算符 |
| ::     | 域运算符           |
| ?:     | 条件运算符         |
| sizeof | 长度运算符         |
| #      | 预处理符号         |

### 3. 继承

作用：允许使用一个类来定义另一个类，从而提高代码的复用性。

#### 基类和派生类

被继承的类称为**基类**，继承的类称为**派生类**。 一个类可以派生自多个类（多继承）。

`class derived-class: access-specifier base-class`

deriver-class 是派生类，base-class 是基类或者基类列表，access-specifier 是访问修饰符。

#### 派生类的权限

父类：

| 访问   | public | protected | private |
| ------ | ------ | --------- | ------- |
| 同类   | true   | true      | true    |
| 派生类 | true   | true      | false   |
| 外部   | true   | false     | false   |

#### 继承类型

access-specifier 是访问修饰符，可以是 public、protected、private。

| 访问修饰符 | 继承类型 | 继承规则                                                     |
| ---------- | -------- | ------------------------------------------------------------ |
| public     | 公有继承 | public -> public, protected -> protected, private -> private |
| protected  | 保护继承 | public，protected -> protected, private -> private           |
| private    | 私有继承 | public, protected, private -> private                        |

#### 多继承

一个子类可以同时继承多个父类的属性.

格式： class 子类名: 访问权限 父类名 1, 访问权限 父类名 2, ...

当出现重名的成员时，需要使用作用域解析运算符来指明调用的是哪个类的成员。

### 4. 多态

#### 虚函数实现多态

c++ 多态性是允许将父类的指针赋值给子类的指针。多态性是通过虚函数实现的。

实现方法：在基类中声明虚函数，在派生类中重写该函数。 虚函数的作用是告诉编译器不要静态链接到该函数，而是在运行时确定函数的调用。

```cpp
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
```

这会输出："this is class A" "this is class B" "this is class C"。如果不使用虚函数，那么输出的都是"this is class A"。

#### 纯虚函数

您可能想要在基类中定义虚函数，以便在派生类中重新定义该函数更好地适用于对象，但是您在基类中又不能对虚函数给出有意义的实现，这个时候就会用到纯虚函数。**纯虚函数是一种在基类中声明的虚函数，它在基类中没有定义，但是在派生类中必须定义。**
