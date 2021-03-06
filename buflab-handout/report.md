# The Buffer Bomb 大作业报告

姓名：骆炳君

班级：软件71

学号：2017013573

## 题目说明

### Level0: Candle

在getbuf()函数中，返回地址存储在栈中0x55683214处，其值为0x08048bf3（指向test()函数中的下一行），利用缓冲区溢出将栈中地址0x55683214以下的区域值设为0x90，并将0x55683214处的值修改为0x08048b04（指向smoke()函数），就可以在getbuf()函数执行到ret指令时返回至smoke()函数.

### Level1: Sparkler

分析fizz()函数中的指令可以得出，val变量存储在0x8(%ebp)中，对应地址为0x5568321c，即Level0中返回地址以上8个字节处，cookie变量是全局变量，存储地址为0x0804e104，在运行时值为0x2ef2f33f.

参考Level0中的操作，可以利用缓冲区溢出将getbuf()函数的返回地址设为0x08048b2e（指向fizz()函数），并将其以上8个字节的0x5568321c处的值（对应val）修改至与cookie相等，即可返回到fizz()并通过检验.

### Level2: Firecracker

与Level0和1相比，Level2不仅要求修改栈中的值，还需要修改全局变量global_value的值，也就是要利用缓冲区溢出执行攻击者的汇编指令.

#### 设计汇编代码

```assemble
   0:	bb 3f f3 f2 2e       	mov    $0x2ef2f33f,%ebx
   5:	89 1d 0c e1 04 08    	mov    %ebx,0x804e10c
   b:	68 82 8b 04 08       	push   $0x8048b82
  10:	c3                   	ret    
```

mov指令不允许直接把内存设置为立即数，运行程序发现%ebx未被使用，所以首先把0x2ef2f33f（cookie值）暂存到%ebx中.分析bang()中代码可得global_value变量的地址为0x804e10c，再把%ebx的值移入到这个地址.

完成修改操作后，程序需要返回到bang()函数，把0x8048b82（指向bang()函数）压入栈中，最后执行ret指令即可.

#### 将汇编代码插入栈中并执行

在本程序中，缓冲区注入攻击的最佳入口是getbuf()函数的返回地址.和前3个Level类似，可以将上述汇编代码插入到返回地址以上的栈中，再把函数getbuf()的返回地址设置为汇编代码的开头.

### Level3: Dynamite

#### 设计汇编

```assemble
   0:	b8 3f f3 f2 2e       	mov    $0x2ef2f33f,%eax
   5:	bd 40 32 68 55       	mov    $0x55683240,%ebp
   a:	68 f3 8b 04 08       	push   $0x8048bf3
   f:	c3                   	ret   
```

分析getbuf()函数中的指令不难看出，其返回值存储在%eax寄存器中，使用mov指令就可以修改这个值.但同时，由于test()函数的栈底指针%ebp存储在getbuf()函数的返回地址以下4个字节处，在缓冲区溢出过程中会被覆盖掉，所以需要手动设置%ebp为正确的栈底地址.完成这些任务之后，将返回地址压入栈中，再执行ret指令即可.

#### 将汇编代码插入栈中并执行

这部分操作与Level2类似，但由于程序要返回到test()函数中继续执行，需要尽量减少对栈帧的破坏，所以选择将汇编代码插入到返回地址以下的栈中，这样返回到test()函数后不会损坏原有的栈帧.

### Level4: Nitroglycerin

#### 设计汇编代码

```assemble
   0:	b8 3f f3 f2 2e       	mov    $0x2ef2f33f,%eax
   5:	ba 28 00 00 00       	mov    $0x28,%edx
   a:	8d 2c 14             	lea    (%esp,%edx,1),%ebp
   d:	68 67 8c 04 08       	push   $0x8048c67
  12:	c3                   	ret    
```

和Level3类似，首先将返回值设置为0x2ef2f33f（cookie值），然后手动设置%ebp.由观察可得栈顶与栈底间的长度为0x28，所以把%ebp设置为%esp+0x28.完成任务将返回地址压栈，并执行ret指令即可.

#### 将汇编代码插入栈中并执行

由于Level5中栈空间的随机性，从而导致缓冲区开始地址和返回值地址都在一定范围内变化.用GDB调试bufbomb -n，测得每一次运行的栈参数如下：

| 缓冲区开始地址 | 返回地址 | 长度 |
| ------ | ------ | ------ |
|0x55683008|0x55683214|0x20c|
|0x55683008|0x55683214|0x20c|
|0x55683028|0x55683234|0x20c|
|0x55683058|0x55683264|0x20c|
|0x55682fd8|0x556831e4|0x20c|

可以发现，5次缓冲区溢出的公共地址段为0x55683058~0x556831e4，因此将0x55683058设置为getbufn()的返回地址，在返回地址以下的栈中插入汇编代码，并在汇编代码前全部用0x90占位.

## 实验感想

实验兼具趣味性和挑战性，帮助我深入理解了程序运行过程中栈的行为，同时还熟悉了GDB的基本调试操作，感谢老师和助教的工作！