# 笔试总结

### c++ 输入输出

- 键盘输入字符串，按回车字符串送入到缓冲区，同时这个回车被转换成一个换行符'\n'也送入缓冲区，比如“123 回车”，那么送入缓冲区的是"123\n"，缓冲区的长度是四个字节。

#### 输入

- cin: 标准输入流，从缓冲区读取数据

**分隔符：分隔符有空格、tab 和换行符**

如果缓冲区是空的，则阻塞等待；如果缓冲区第一个是分隔符，则清除这个分隔符往下读，否则就正常往下读，读到下一个分隔符为止。**但是注意 cin 不处理截至时后面这个分隔符，会把它留在缓冲区！**

---

- cin.get(): 读取单个或指定长度的字符，包括空白字符
  - **读取一个字符：总结就是啥都不管直接从缓冲区读一个**

  ```cpp
  ```

char var = cin.get();
istream& cin.get(char& var);

```
	- **读取固定长度字符串**
	```cpp
istream& get ( char* s, streamsize n );
istream& get ( char* s,  streamsize  n, char delim );
```

**读取固定长度字符串的时候，delim 是指定结束符，默认是换行符，会残留在缓冲区。**

---

- cin.getline(): 读取指定长度的字符，不包括终止字符，包括空白字符，模板如下：

```cpp
istream& getline(char* s, streamsize count); //默认以换行符结束
istream& getline(char* s, streamsize count, char delim);
```

`char a[n]; cin.getline(a, n, '\n');` ：cin.getline()与 cin.get()指定读取长度时的用法几乎一样。区别在于，**cin.getline 不会将结束符或者换行符残留在输入缓冲区中。**

---

- getline(cin, str): 并不是标准输入流的函数，而是字符串流 sstream 的函数，要包含头文件<string>

`string str; getline(cin, str);`：读取字符串，包括空白字符，但不包括终止字符'\n'，读取的字符存放在 str 中。直到读到换行符或者文件结束符 EOF 为止，所以缓冲区不存在残留字符。

### 二叉树结构体

```cpp
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    // 构造函数
    TreeNode(int x): val(x), left(NULL), right(Null){};
}
```

### 链表结构体

```cpp
_ // 定义链表节点_
_struct ListNode{_
_    int val; // 节点的值_
_    ListNode *next; // 指向下一个节点_
_    /*  节点的构造函数，cpp有一个默认的构造函数，默认是无参数的构造，不能传入参数_
_        但是可以像下面一样自定义一个构造函数，但是必需按照构造来传入参数，不然报错    _
_    */_
_    ListNode(int x): val(x), next(NULL) {}_
_};_
```

### 优先级队列

#### 小根堆

`priority_queue<int, vector<int>, greater<int>> p`

#### 大根堆

`priority_queue<int, vector<int>, less<int>> p`

#### **自定义比较函数**

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
