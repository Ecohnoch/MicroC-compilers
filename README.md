# MicroC-compilers

# 项目背景

与教编译原理的老师刘馨月副教授联系后，老师给予了我一篇她正在写的论文即Micro C编译演示系统。于是我参考论文上的语法语义搭建了这个语言的编译器，并且赋予了界面和动画，且优化了相关细节，让它看上去更像一个正常的软件。

环境：macOS-10.13.4，Qt-5.7，Qt-Quick-2.7

主要使用编程语言：C++（内核）、QML（界面）

源代码：https://github.com/Ecohnoch/MicroC-compilers

性质：全独立自主实现

时间：2017年5-6月

# 项目介绍

## 实现功能

这个编译器主要实现了下面这些功能：

* Micro C编译器前端：
    * 词法分析
    * 语法分析
    * 语义分析
* 相关动态特效
* 文本文件读取/保存/示例
* 三种可切换皮肤
* 中英语言切换

## Micro C语法简单介绍

主要包含五种语句：

* bool语句
* 计算语句
* 赋值语句
* if..else选择语句
* while循环语句

所有记号是：

```
if、else、while
{、}、；、#、+、*、=、==、&&、||、！、>、>=、<、<=、(、)
```

## 展示

首先是主界面：

![image](/img/mic1.png){:height="50%" width="50%"}

然后是词法分析，分析结果均在下方的表中：

![image](/img/mic11.png){:height="50%" width="50%"}

然后是语法分析，构建语法树，语法树也在下方的表中，按层数索引，三角箭头打开一层：

![image](/img/mic2.png){:height="50%" width="50%"}

第一层的五个兄弟分别是：if Bool S else S：

![image](/img/mic6.png){:height="50%" width="50%"}

语法树的一个局部：

![image](/img/mic7.png){:height="50%" width="50%"}

然后是语义分析，所有变量的每一次更新都会显示：

![image](/img/mic3.png){:height="50%" width="50%"}

我给了几个示例代码，点击相应的名字就会出现相应的代码：

![image](/img/mic8.png){:height="50%" width="50%"}

还有皮肤系统，目前就两个：

![image](/img/mic4.png){:height="50%" width="50%"}

![image](/img/mic5.png){:height="50%" width="50%"}

还有语言系统，目前只包括中文和英文：

![image](/img/mic9.png){:height="50%" width="50%"}

最后是一个关于界面：

![image](/img/mic10.png){:height="50%" width="50%"}


