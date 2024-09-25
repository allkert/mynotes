[TOC]

## CppFunc

### 哈希表

常见的三种哈希表的实现方式：数组，set，map

- 数组
- set

![alt text](image1.png)

- map

![alt text](image2.png)

### 对函数名取地址(对函数名的理解)

举下面的例子：

```cpp
int add(){
   return 1;
}
int main(){
   // 输出函数add的地址
   cout << add << endl;
   // 对add取地址
   cout << &add << endl;
   // 对函数名取内容
   cout << *add << endl;
   // 结果是一样的地址，但是返回类型不同
   cout << typeid(add).name() << endl;
   cout << typeid(&add).name() << endl;
   cout << typeid(*add).name() << endl;
}
```

只有中间那个的类型是函数指针，其他两个都不是。

func 得到函数地址，是因为它是**函数指示符**。**只有在作为 sizeof 或者单目运算符&取地址时候，它的类型才是函数;其它情况都会被转化为指向该函数的指针**。所以&func 和 func 都会得到函数的地址,*func 时候返回函数地址则是一种默认规定。

### 迭代器

- 迭代器

| 功能      | 描述                                 |
| --------- | ------------------------------------ |
| begin()   | 返回指向 set 开始的迭代器            |
| cbegin()  | 返回指向 set 开始的 const 迭代器     |
| end()     | 返回指向 set 结尾的迭代器            |
| cend()    | 返回指向 set 结尾的 const 迭代器     |
| rbegin()  | 返回指向 set 结尾的逆向迭代器        |
| Rend()    | 返回指向 set 开始的逆向迭代器        |
| crbegin() | 返回指向 set 结尾的逆向 const 迭代器 |
| crend()   | 返回指向 set 开始的逆向 const 迭代器 |

- 容量

| 功能       | 描述                           |
| ---------- | ------------------------------ |
| size()     | 返回容器中元素的数目           |
| max_size() | 返回容器能容纳的元素的最大数目 |
| empty()    | 判断容器是否为空               |

- 修改器

| 功能           | 描述                      |
| -------------- | ------------------------- |
| insert()       | 在 set 容器中插入元素     |
| erase()        | 删除 set 容器中的元素     |
| swap()         | 交换两个 set 容器         |
| clear()        | 清除 set 容器中的所有元素 |
| emplace()      | 在 set 容器中插入元素     |
| emplace_hint() | 在 set 容器中插入元素     |

- 查找

| 功能          | 描述                                           |
| ------------- | ---------------------------------------------- |
| count()       | 返回指定元素出现的次数                         |
| find()        | 查找指定元素                                   |
| lower_bound() | 返回指向大于（或等于）某值的第一个元素的迭代器 |
| upper_bound() | 返回指向大于某值的第一个元素的迭代器           |
| equal_range() | 返回与指定值相等的上下限的两个迭代器           |

- 迭代器的分类和支持的操作

| 类型           | 描述                         | 支持的遍历操作                       | 使用该类型的容器                          |
| -------------- | ---------------------------- | ------------------------------------ | ----------------------------------------- |
| 输入迭代器     | 提供对数据的只读访问         | ++, ==, !=                           |                                           |
| 输出迭代器     | 提供对数据的只写访问         | ++, ==, !=                           |                                           |
| 前向迭代器     | 可以读写数据                 | ++, ==, !=                           | list, slist, set, multiset, map, multimap |
| 双向迭代器     | 可以双向读写数据             | ++, --, ==, !=                       | list, slist, set, multiset, map, multimap |
| 随机访问迭代器 | 可以以随机访问的方式读写数据 | ++, --, ==, !=, >, <, >=, <=, +n, -n | vector, deque, string, array              |

### String

- string 中 length()和 size()和 sizeof()的区别

length()和 size()是 string 类的成员函数，返回 string 的长度，sizeof()是 C++ 的一个操作符，返回对象或类型的大小。

- string 和 int 之间的转换

int 转 string：

| 序号 | 方法                                                                         | 描述                                                                   |
| ---- | ---------------------------------------------------------------------------- | ---------------------------------------------------------------------- |
| 1    | to_string()函数                                                              | C++11 标准引入的函数                                                   |
| 2    | stringstream 类                                                              | C++ 标准库中的类                                                       |
| 3    | sprintf()函数                                                                | C 标准库中的函数                                                       |
| 4    | int stoi(const string& str, size_t* pos = 0, int base = 10)                  | size_t 是一个无符号整数类型，typedef unsigned int size_t;, base 是进制 |
| 5    | long stol(const string& str, size_t* pos = 0, int base = 10)                 |                                                                        |
| 6    | long long stoll(const string& str, size_t* pos = 0, int base = 10)           |                                                                        |
| 7    | unsigned long stoul(const string& str, size_t* pos = 0, int base = 10)       |                                                                        |
| 8    | unsigned long long stoull(const string& str, size_t* pos = 0, int base = 10) |                                                                        |
| 9    | float stof(const string& str, size_t* pos = 0)                               |                                                                        |
| 10   | double stod(const string& str, size_t* pos = 0)                              |                                                                        |
| 11   | long double stold(const string& str, size_t* pos = 0)                        |                                                                        |
| 12   | double stod(const string& str, size_t* pos = 0)                              |                                                                        |

4-12 都包含头文件 string 中

```cpp
int a = 123;
// 1. to_string()函数
string str = to_string(a);
// 2. stringstream类
ostringstream oss;
oss << a;
string str = oss.str();
// 3. sprintf()函数
char buf[100];
sprintf(buf, "%d", a);
string str = buf;
```

string 转 int：

1. istream 类: istringstream
2. scanf()函数
3. atoi()函数

```cpp
string str = "123";
// 1. istream类: istringstream
int a;
istringstream iss(str);
iss >> a;
// 2. scanf()函数
int a;
sscanf(str.c_str(), "%d", &a);
// 3. atoi()函数
int a = atoi(str.c_str());
```

### reverse

reverse()函数是 C++ 标准库中的函数，用于反转字符串和数组以及容器中的元素。输入参数是两个迭代器，分别指向要反转的元素的起始位置和结束位置。reverse()函数会将这两个迭代器之间的元素反转。

### queue

queue 提供的操作有：

- push()：在队尾插入一个元素
- pop()：在队头删除一个元素
- front()：返回队头元素
- back()：返回队尾元素
- empty()：判断队列是否为空
- size()：返回队列中元素的个数

queue 库提供的类：

1. queue：普通队列
2. priority_queue：优先队列

定义方法：priority_queue< 元素类型 > 变量名;

#### priority_queue

priority_queue 包括在头文件<queue>中，定义方法：

```cpp
priority_queue<type, container, compare> name;
```

其中，type 是元素类型，container 是容器类型，compare 是比较类型。最简单的定义方式为：

`priority_queue<int> q;`，后两个参数默认为 vector 和 less，即默认是大顶堆。如果第三个参数为 greater，则是小顶堆。

```cpp
priority_queue<int, vector<int>, less<int>> q;//大顶堆
priority_queue<int, vector<int>, greater<int>> q;//小顶堆
```

- **自定义比较函数**

**比较函数的作用是用来判断第一个参数的优先级是否低于第二个参数。**

通过运算符重载来自定义比较函数，可以见 leetcode 第 347 题的解法。自定义比较函数有以下方法：

1. struct 重载()运算符

```cpp
struct cmp{
    bool operator()(int a, int b){
        return a > b;
    }
};
```

1. class 重载()运算符

```cpp
class cmp{
public:
    bool operator()(int a, int b){
        return a > b;
    }
};
```

1. 自定义函数

decltype()函数：decltype 是 C++11 标准引入的关键字，用于获取变量的类型。在定义函数指针时，如果函数的返回值类型是 auto，那么编译器无法推断函数指针的类型。

decltype()函数和 auto 的区别：

- auto 根据=右边的初始值推导出变量的类型，decltype 根据 exp 表达式推导出变量的类型，跟=右边的 value 没有关系
- auto 要求变量必须初始化，这是因为 auto 根据变量的初始值来推导变量类型的，如果不初始化，变量的类型也就无法推导，而 decltype 不要求。

这种情况下，需要 decltype()函数，用于获取函数指针的类型。

```cpp
bool cmp(int a, int b){
    return a > b;
}
priority_queue<int, vector<int>, decltype(&cmp)> q(cmp);
```

1. lambda 表达式

```cpp
auto cmp=[](vector<int>&a,vector<int>&b)->bool{
            return a[0]>b[0];
        };
priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> q(cmp);//小顶堆
```

### vector

- vector< 变量类型 > 变量名; //声明一个 vector

| 方法                               | 描述                         | 备注                                   |
| ---------------------------------- | ---------------------------- | -------------------------------------- |
| push_back()                        | 在 vector 的末尾添加一个元素 |                                        |
| pop_back()                         | 删除 vector 的最后一个元素   |                                        |
| std::find(v.begin(), v.end(), key) | 在 vector 中查找指定元素     | 注意这个和 map、set 的 find 方法不一样 |
| v.erase(v.begin() + i)             | 删除 vector 中的第 i 个元素  |                                        |

### map、set

- map< key 类型, value 类型 > 变量名; //声明一个 map

map 提供的操作有：

| 方法                                                 | 描述                  | 备注           |
| ---------------------------------------------------- | --------------------- | -------------- |
| void insert(pair<key 类型, value 类型 >(key, value)) | 在 map 中插入元素     |                |
| map.find(key)                                        | 在 map 中查找指定元素 | 返回一个迭代器 |
| map.erase(key)                                       | 删除 map 中的指定元素 |                |
| map.erase(map.begin(), map.end())                    | 删除 map 中的所有元素 |                |
| map.clear()                                          | 删除 map 中的所有元素 |                |
| map.size()                                           | 返回 map 中元素的个数 |                |
| map.empty()                                          | 判断 map 是否为空     |                |

- map 排序

### unordered_map 自定义 hash 函数

unordered_map 使用模板：unordered_map<T, U, Hash, Pred, Alloc>

- T: 键的类型
- U: 值的类型
- Hash: hash 函数，用于计算键的 hash 值
- Pred: 判断两个键是否相等的函数
- Alloc: 分配器

```cpp
// 方法1：struct
struct MyHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};
// 方法2：lambda
auto myHash = [](const pair<int, int>& p) {
    return hash<int>()(p.first) ^ hash<int>()(p.second);
};
// 方法3：自定义类
class MyHash {
public:
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};
```

### tree

#### 二叉树的种类

1. 满二叉树：一个二叉树，如果每一个层的结点数都达到最大值，则这个二叉树就是满二叉树。
2. 完全二叉树：对于一颗具有 n 个结点的二叉树按层序编号，如果编号为 i 的结点与同样深度的满二叉树中编号为 i 的结点在二叉树中位置完全相同，则这颗二叉树称为完全二叉树。
3. 二叉搜索树：左子树上所有结点的值均小于它的根结点的值，右子树上所有结点的值均大于它的根结点的值。or  完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。
4. 二叉搜索树：左子树上所有结点的值均小于它的根结点的值，右子树上所有结点的值均大于它的根结点的值。
5. 平衡二叉搜索树：是一种特殊的二叉搜索树，它或者是一棵空树，或者是具有以下性质的二叉树：它的左子树和右子树都是平衡二叉树，且左子树和右子树的深度之差的绝对值不超过 1。

#### 二叉树的定义

```cpp
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    // 构造函数
    TreeNode(int x): val(x), left(NULL), right(Null){};
}
```

### stack

1. stack 的初始化

```cpp
//1、创建一个空的栈s1
stack<int> s1;
stack<int,list<int>> s1;
 
//2、用vector容器初始化stack
vector<int> v1={1,2,3,4};
stack<int,vector<int>> s2(v1);   //1,2,3,4依次入栈
 
//3、用deque容器初始化stack
//用deque为stack初始化时deque可省  因为stack是基于deque实现的, 默认以deque方式构造
deque<int> d1 = {1,2,3,4,5};
stack<int,deque<int>> s3(d1);
stack<int> s4(d1);  
 
//4、用list容器初始化stack
list<int> l1 = {1,2,3,4,5};
stack<int,list<int>> s5(l1)
```

### accumulate 函数

accumulate 函数是 C++ 标准库中的函数，用于计算区间内元素的累加值。accumulate 函数的定义如下：

```cpp
_unsigned_ _int_ std::accumulate<_const_ _int_ *, _unsigned_ _int_, lambda [](_size_t_ acc, _int_ num)->_unsigned_ _long_ _long_>(_const_ _int_ *__first, _const_ _int_ *__last, _unsigned_ _int_ __init, lambda [](_size_t_ acc, _int_ num)->_unsigned_ _long_ _long_ __binary_op)
```

accumulate(起始迭代器, 结束迭代器, 初始值, 自定义操作函数)

acc 是之前累加的值，num 是当前值

### upper_bound 和 lower_bound

- lower_bound()函数是 C++ 标准库中的函数，用于在有序序列中查找第一个大于或等于某个值的元素的位置。lower_bound()函数的定义如下：

```cpp
lower_bound(first, last, val);
```

**lower_bound()还可以自定义比较函数，方法如下：**

```cpp
lower_bound(first, last, val, cmp);
// cmp可以是匿名函数，和优先级队列的自定义比较函数差不多
auto it = lower_bound(v.begin(), v.end(), val, [](int a, int b){
    return a < b;
});
```

- upper_bound()函数是 C++ 标准库中的函数，用于在有序序列中查找第一个大于某个值的元素的位置。

### lambda 表达式

- lambda 表达式的四种写法

1. `[captures]<tparams>(params)lambda-specifier{body}`
2. `[captures](params)trailling-return-type{body}`
3. `[captures](params){body}`
4. `[captures]lambda-specifier{body}`

- captures: 捕获列表，lambda 可以把上下文中的变量捕获到 lambda 中，捕获列表可以是值传递，引用传递，隐式捕获等

[ ]什么也不捕获

[=] 以值传递的方式捕获所有的局部变量

[&] 以引用传递的方式捕获所有的局部变量

[=, &x] 以值传递的方式捕获所有的局部变量，但是 x 以引用传递的方式捕获

[&, x] 以引用传递的方式捕获所有的局部变量，但是 x 以值传递的方式捕获

[this] 捕获 this 指针

- tparams: 模板参数列表
- params: 形参列表
- lambda-specifier: lambda 表达式的特殊说明符
- trailling-return-type: 返回值类型，一般可以省略
- body: 函数体

### std::array 的用法

#### 定义

array 用来定义一个指定数据类型,固定大小的数组,它是一个类模板,定义在头文件<array>中,它的模板如下:

`array<typename T, size_t N> arrayName;`

其中 T 是数组元素的数据类型,N 是数组的大小,它的大小是固定的,不能改变,它的大小必须是一个常量表达式,不能是变量。

array 的初始化方法有很多种,下面是一些常用的初始化方法:

```cpp
array<int, 5> arr1 = {1, 2, 3, 4, 5}; // 初始化一个大小为5的数组,并赋值
array<int, 5> arr2 = {1, 2}; // 初始化一个大小为5的数组,并赋值,没有赋值的元素会被初始化为0

int m = 5;
array<int, m> arr3 = {1, 2, 3, 4, 5}; // 错误,数组的大小必须是一个常量表达式

// 注意两个数组的大小必须相同
array<int, 5> arr4 = arr1; // 拷贝构造函数,将arr1拷贝给arr4

// 不能用int[]数组初始化array
int arr5[] = {1, 2, 3, 4, 5};
array<int, 5> arr6 = arr5; // 错误
```

#### 访问

1. at: `arr.at(i)` 返回数组中第 i 个元素的引用,如果 i 越界,会抛出一个 out_of_range 异常
2. operator[]: `arr[i]` 返回数组中第 i 个元素的引用,如果 i 越界,不会抛出异常,但是会导致未定义行为
3. front: `arr.front()` 返回数组中第一个元素的引用
4. back: `arr.back()` 返回数组中最后一个元素的引用
5. data: `arr.data()` 返回指向数组首元素的指针

#### 属性

1. size: `arr.size()` 返回数组的当前大小
2. max_size: `arr.max_size()` 返回数组的最大容量,由于数组的大小是固定的,所以 max_size 和 size 是相等的
3. empty: `arr.empty()` 返回数组是否为空
4. fill: `arr.fill(val)` 将数组中的所有元素都赋值为 val
5. swap: `arr1.swap(arr2)` 交换两个数组的元素,两个数组的大小必须相同

#### 支持迭代器
