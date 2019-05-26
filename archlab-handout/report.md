# ArchLab大作业报告

姓名：骆炳君

班级：软件71

学号：2017013573

## Part A

在实验过程中，借助gcc将examples.c中的函数转换为汇编代码，再更改其中的部分指令使之符合Y86指令集即可.

```bash
$ gcc -O1 -S exampls.c
```

### sum_list

原始汇编代码：

```assembly
sum_list:
	testq	%rdi, %rdi
	je	L4
	movl	$0, %eax
L3:
	addl	(%rdi), %eax
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	jne	L3
	rep ret
L4:
	movl	$0, %eax
	ret
```

增加维护栈指针的指令，根据需要改变寄存器，把movl指令替换为irmovl指令，testq指令替换为andl指令，addl指令拆分为mrmovl指令和addl指令.

函数需要1个参数ls，返回值存储在寄存器变量%eax中.

### rsum_list

原始汇编代码：

```assembly
rsum_list:
	movl	$0, %eax
	testq	%rdi, %rdi
	jne	L13
	rep ret
L13:
	pushq	%rbx
	movq	%rdi, %rbx
	movq	8(%rdi), %rdi
	call	rsum_list
	addl	(%rbx), %eax
	popq	%rbx
	ret
```

和前面类似进行更改. 

函数需要1个参数ls，返回值存储在寄存器变量%eax中.

### copy_block

原始汇编代码：

```assembly
copy_block:
	movl	$0, %ecx
	testl	%edx, %edx
	jle	L15
L13:
	movl	(%rdi), %eax
	addq	$4, %rdi
	movl	%eax, (%rsi)
	addq	$4, %rsi
	xorl	%eax, %ecx
	decl	%edx
	testl	%edx, %edx
	jg	L13
L15:
	movl	%ecx, %eax
	ret
```

和前面类似，并将自减指令decl拆分为irmovl指令和addl指令.

函数需要3个参数src、dest和len，返回值存储在寄存器变量%eax中.

## Part B

### iaddl

分阶段处理情况：

```
Fetch		icode:ifun <- M1[PC]
			rA:rB <- M1[PC+1]
			valC <- M4[PC+2]
			valP <- PC+10
Decode		valB <- R[rB]
Excode		valE <- valB+valC
			Set CC
Memory
Write back	R[rB] <- valE
PC update	PC <- valP
```


#### SEQ

在Fetch阶段，将IIADDL加入instr_valid、need_regids和need_valC中. 在Decode阶段，把srcB设置为REBP，dstE设置为rB. 在Execute阶段，把aluA设置为valC，aluB设置为valB，把IIADDL加入set_cc中.

#### PIPE

和SEQ中的设置大体相同，由于不访问内存，不存在加载/使用冒险，所以不更改寄存器流水线控制部分.

### leave

分阶段处理情况：

```
Fetch		icode:ifun <- M1[PC]
			valP <- PC+1
Decode		valA <- R[%ebp]
Excode 		valE <- valA + 4
Memory		valM <- M4[valA]
Write back	R[%esp] <- valE
			R[%ebp] <- valM
PC update	PC <- valP
```

#### SEQ

在Fetch阶段，将ILEAVE加入instr_valid中. 在Decode阶段，把srcA设置为REBP，dstE设置为RESP，dstM设置为REBP. 在Execute阶段，把aluA设置为valA，aluB设置为4. 在Memory阶段，将ILEAVE加入mem_read中，并将mem_addr设置为valA.

#### PIPE

和SEQ中的设置大体相同，由于需要访问内存，存在加载/使用冒险，还需设置流水线寄存器的气泡和暂停. 在F_stall、D_stall和E_bubble中加入ILEAVE的情形. 同时设置D_bubble，在加载/使用冒险和ret指令组合时阻止气泡插入.