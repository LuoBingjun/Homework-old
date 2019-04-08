### 1.

将单位圆按$d$均分为$n$个面积相等的圆环，设第$i$个圆环的内径为$a_i$，外径为$a_{i+1}$，$i=0,2,\cdots,n-1$，则有
$$a_0=0,\ \pi(a_{i+1}^2-a_i^2)=\frac{\pi}{n}$$
得
$$a_{i+1}=\sqrt{a_i^2+\frac{1}{n}}$$
所以
$$a_i=\sqrt{\frac{i}{n}}$$
可以将$d$分为$n$个区间$(a_i,a_{i+1}](i=0,2,\cdots,n-1)$，其中
$$i< d^2n\le i+1$$

算法如下：

```
n = A.length
for i = 1 to n
	k = ⌈d*d*n⌉-1
	do insert A[i] into list B[k]
for i = 0 to n − 1
	do sort list B[i] with insertion sort
	concatenate the lists B[0], B[1], ..., B[n − 1] together in order
```

### 2.

算法如下：

```
let r[0..n] be a new array
r[0] = 0
for j = 1 to n
	q = −∞
	for i = 1 to j
		q = max(q, p[i] + r[j − i] - c)
		r[j] = q
return r[n]
```

