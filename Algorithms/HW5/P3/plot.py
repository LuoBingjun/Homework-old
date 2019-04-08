import matplotlib.pyplot as plt
import pandas as pd
import math
import numpy as np
from scipy.interpolate import spline

data=[]

methods=['insertion','shell','quick','merge','radix']
names=['Insertion Sort','Shellsort','Quicksort','Merge sort','Radix sort']
colors=['r','y','g','c','b']

for i in methods:
    df=pd.read_csv(i + '_sort.csv')
    df['time']=df['time'].apply(lambda x:math.log(x,10))
    df['n']=df['n'].apply(lambda x:math.log(x,10))
    data.append(df)

for i in range(5):
    # plt.plot(data[i]['n'],data[i]['time'],colors[i],label=names[i])
    xnew = np.linspace(data[i]['n'].min(),data[i]['n'].max(),25) #300 represents number of points to make between T.min and T.max
    power_smooth = spline(data[i]['n'],data[i]['time'],xnew)
    for j in range(len(xnew)):
        if xnew[j] <= 3 or (i>0 and xnew[j] <= 4):
            power_smooth[j]=0
    plt.plot(xnew,power_smooth,colors[i],label=names[i])


# plt.plot(data1['population'],data1['time'],'b',label='Flow-controlled Model')
# plt.plot(data2['population'],data2['time'],'g',label='Flow-distributed Model')
plt.grid(True)
plt.xlabel('$log_{10}}$ of n')
plt.ylabel('$log_{10}$ of running time')
plt.legend(loc='upper left', borderaxespad=0.)
plt.show()