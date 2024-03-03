## 基本语法
### 哈希表
常见的三种哈希表的实现方式：数组，set，map
* 数组
* set
![alt text](image1.png)
* map
![alt text](image2.png)  
### 迭代器
* 迭代器  

| 功能 | 描述 |
| --- | --- |
| begin() | 返回指向 set 开始的迭代器 |
| cbegin() | 返回指向 set 开始的 const 迭代器 |
| end() | 返回指向 set 结尾的迭代器 |
| cend() | 返回指向 set 结尾的 const 迭代器 |
| rbegin() | 返回指向 set 结尾的逆向迭代器 |    
| Rend() | 返回指向 set 开始的逆向迭代器 |
| crbegin() | 返回指向 set 结尾的逆向 const 迭代器 |
| crend() | 返回指向 set 开始的逆向 const 迭代器 |  

* 容量  

| 功能 | 描述 |
| --- | --- | 
| size() | 返回容器中元素的数目 |
| max_size() | 返回容器能容纳的元素的最大数目 |
| empty() | 判断容器是否为空 |
* 修改器
| 功能 | 描述 |
| --- | --- |
| insert() | 在 set 容器中插入元素 |
| erase() | 删除 set 容器中的元素 |
| swap() | 交换两个 set 容器 |
| clear() | 清除 set 容器中的所有元素 |
| emplace() | 在 set 容器中插入元素 |
| emplace_hint() | 在 set 容器中插入元素 | 

* 查找  

| 功能 | 描述 |
| --- | --- |
| count() | 返回指定元素出现的次数 |
| find() | 查找指定元素 |
| lower_bound() | 返回指向大于（或等于）某值的第一个元素的迭代器 |
| upper_bound() | 返回指向大于某值的第一个元素的迭代器 |
| equal_range() | 返回与指定值相等的上下限的两个迭代器 |

### String
* string中length()和size()和sizeof()的区别  
length()和size()是string类的成员函数，返回string的长度，sizeof()是C++的一个操作符，返回对象或类型的大小。

* string和int之间的转换
int转string：   

|序号|方法|描述|
|---|---|---|
|1|to_string()函数|C++11标准引入的函数|
|2|stringstream类|C++标准库中的类|
|3|sprintf()函数|C标准库中的函数|
|4|int stoi(const string& str, size_t* pos = 0, int base = 10)|size_t 是一个无符号整数类型，typedef unsigned int size_t;, base是进制|
|5|long stol(const string& str, size_t* pos = 0, int base = 10)||
|6|long long stoll(const string& str, size_t* pos = 0, int base = 10)||
|7|unsigned long stoul(const string& str, size_t* pos = 0, int base = 10)||
|8|unsigned long long stoull(const string& str, size_t* pos = 0, int base = 10)||
|9|float stof(const string& str, size_t* pos = 0)||
|10|double stod(const string& str, size_t* pos = 0)||
|11|long double stold(const string& str, size_t* pos = 0)||
|12|double stod(const string& str, size_t* pos = 0)||
*4-12都包含在string头文件中*
```c++
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
string转int：
1. istream类: istringstream
2. scanf()函数
3. atoi()函数
```c++
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
reverse()函数是C++标准库中的函数，用于反转字符串和数组以及容器中的元素。输入参数是两个迭代器，分别指向要反转的元素的起始位置和结束位置。reverse()函数会将这两个迭代器之间的元素反转。

### queue
queue提供的操作有：
* push()：在队尾插入一个元素
* pop()：在队头删除一个元素
* front()：返回队头元素
* back()：返回队尾元素
* empty()：判断队列是否为空
* size()：返回队列中元素的个数


### vector
* vector< 变量类型 > 变量名; //声明一个vector
| 方法 | 描述 | 备注 |
| --- | --- | --- |
| push_back() | 在vector的末尾添加一个元素 |    |
| pop_back() | 删除vector的最后一个元素 |   |
| std::find(v.begin(), v.end(), key)| 在vector中查找指定元素 | 注意这个和map、set的find方法不一样 |
| v.erase(v.begin() + i) | 删除vector中的第i个元素 |   |

### map、set
* map< key类型, value类型 > 变量名; //声明一个map
map提供的操作有：  

| 方法 | 描述 | 备注 |
| --- | --- | --- |
| void insert(pair<key类型, value类型>(key, value)) | 在map中插入元素 |   |
| map.find(key) | 在map中查找指定元素 | 返回一个迭代器 |
| map.erase(key) | 删除map中的指定元素 |   |
| map.erase(map.begin(), map.end()) | 删除map中的所有元素 |   |
| map.clear() | 删除map中的所有元素 |   |
| map.size() | 返回map中元素的个数 |   |
| map.empty() | 判断map是否为空 |   |  

map排序