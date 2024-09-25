[toc]
# Python学习笔记

## 1. 堆：heapq
注：heapq只提供建立小根堆的方法，建立大根堆的方法：对原值取负号建立小根堆。
`heapq.heapify()`：以线性时间将一个列表转化为小根堆
`heappush(heap,item)`：向堆中push一个item元素
`heappop(heap)`
`heapreplace(heap, item)`:先pop出最小值，然后向堆中push item元素
`heappushpop(heap,item)`:先push进去item，然后再pop一个元素
`nlargest()`：返回heap中n个最大的元素
`nsmallest()`：返回heap中n个最小的元素

## 2. 函数的参数
python的函数的参数在使用时可以按是否改变传入实参的值分为两类：
- 数，str，tuple不会改变原值
- list，dict，set会改变原值  

**所以在传入列表的时候，函数的操作会改变列表的值，如果不想改变的话，可以把`list`改为`list[:]`，这样传入的就是普通的参数了，不会改变原值，这在回溯的时候很有用。**

## 3. `all`函数
all() 函数用于判断给定的可迭代参数 iterable 中的所有元素是否都为 TRUE，如果是返回 True，否则返回 False。元素除了是 0、空、None、False 外都算 True

## 4. argparse模块
```python
import math
import argparse  # 导入argparse模块
# 用来装载参数的容器
parser = argparse.ArgumentParser(description='Calculate volume of a cylinder')
# 给这个解析对象添加命令行参数
parser.add_argument('radius', type=int, help='Radius of cylinder')
parser.add_argument('height', type=int, help='Height of cylinder')
args = parser.parse_args()  # 获取所有参数
def cylinder_volume(radius, height):
    vol = (math.pi) * (radius**2) * (height)
    return vol
if __name__ == '__main__':
    print(cylinder_volume(args.radius, args.height))
```

## 5. shutil模块
shutil 是python中的高级文件操作模块，与os模块形成互补的关系，os主要提供了文件或文件夹的新建、删除、查看等方法，还提供了对文件以及目录的路径操作。shutil模块提供了移动、复制、 压缩、解压等操作，恰好与os互补，共同一起使用，基本能完成所有文件的操作。是一个非常重要的模块。
常用函数：
- `shutil.rmtree(path)`：递归的去删除文件夹

## 6. os模块
`os.path.join()`：连接两个或更多的路径名组件
`os.path.abspath()`：返回path规范化的绝对路径
`os.path.dirname()`：返回path的父目录的路径
`os.path.makedirs()`：创建目录
