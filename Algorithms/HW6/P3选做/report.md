# 实验报告

具体实现一个将图像进行Seam carving的程序，其基本功能是可以将$m\times n$的图象压缩为$m/2\times n/2​$，并且有方便的输入输出功能.


## 实验环境

CPU：Intel Core i5-7200U

内存：8GB

操作系统：Windows 10 64位教育版

编程语言：Python 3.6

运行方式：直接运行seam_carving.exe文件即可

## 算法分析

### 计算破坏度

参考网络资料（[地址](https://zhuanlan.zhihu.com/p/38974520)），选择了能量函数

$$d_1(I)=|\frac{\partial}{\partial x}I|+|\frac{\partial}{\partial y}I|$$

表示图像上每一点的破坏度，计算的时间复杂度为$O(m\times n)​$.

### 查找接缝

采用动态规划算法，详见P3(b)，时间复杂度为$O(m\times n)$.

### 删除接缝

反复调用计算破坏度和查找接缝函数，并逐次删除接缝，直到图片大小达到预期为止，时间复杂度为$O(mn(m+n))​$.

## 结果分析

我们选择分辨率分别为480x300和600x345的几张不同风格的图片，运行了Seam carving算法，结果如下：

![](C:\Projects\Homework\Algorithms\HW6\P3选做\Figure_3.jpg)

![](C:\Projects\Homework\Algorithms\HW6\P3选做\Figure_4.jpg)

![](C:\Projects\Homework\Algorithms\HW6\P3选做\Figure_1.jpg)

结果表明，Seam carving对于大部分图片都能够比较好地保留图片中的关键信息，但也存在着一些问题，例如对复杂形状（如图2和图3中的云）的处理容易变形，对物体边缘的处理不够平滑等.