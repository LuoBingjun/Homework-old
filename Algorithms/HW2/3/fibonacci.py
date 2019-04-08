from math import sqrt
import numpy as np
import pandas as pd

def get_time(func,*args):
    import time
    process_time=0
    for i in range(5):
        start = time.clock()
        try:
            result=func(*args)
        except:
            return -1,-1
        end = time.clock()
        process_time+=(end-start)
    return result,process_time/5

def naive_method(n):
    if n==0:
        return 0
    if n==1:
        return 1
    return naive_method(n-1)+naive_method(n-2)

def squaring_method(n):
    phi=(1+sqrt(5))/2
    def solve(m):
        if m==1:
            return phi
        F=solve(m/2)
        return F*F

    return round(solve(n)/sqrt(5))

def bottomup_method(n):
    F=[0 for i in range(3)]
    F[0]=0
    F[1]=1
    for i in range(2,n+1):
        F[2]=F[0]+F[1]
        F[0]=F[1]
        F[1]=F[2]
    return F[2]

def matrix_method(n):
    F0=np.array([[1,1],[1,0]])

    def multiply(matA,matB):
        m=matA.shape[0]
        matC=np.zeros((m,m))
        for i in range(m):
            for j in range(m):
                for k in range(m):
                    matC[i][j]+=matA[i][k]*matB[k][j]
        return matC

    def solve(m):
        if m==1:
            return F0
        return multiply(solve(m/2),solve(m/2))

    F=solve(n)
    return F[0][1]

n=1
ls1=[]
ls2=[]
ls3=[]
ls4=[]
name=['n','time','result']
for i in range(22):
    n=n*2
    result,time=get_time(naive_method,n)
    ls1.append([n,time,result])
    print(n)
    data=pd.DataFrame(columns=name,data=ls1)
    data.to_csv('fibonacci_naive_method.csv')

    result,time=get_time(squaring_method,n)
    ls2.append([n,time,result])
    print(n)
    data=pd.DataFrame(columns=name,data=ls2)
    data.to_csv('fibonacci_squaring_method.csv')

    result,time=get_time(bottomup_method,n)
    ls3.append([n,time,result])
    print(n)
    data=pd.DataFrame(columns=name,data=ls3)
    data.to_csv('fibonacci_bottomup_method.csv')

    result,time=get_time(matrix_method,n)
    ls4.append([n,time,result])
    print(n)
    data=pd.DataFrame(columns=name,data=ls4)
    data.to_csv('fibonacci_matrix_method.csv')