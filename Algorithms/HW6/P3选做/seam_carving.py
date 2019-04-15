import copy
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
from scipy.ndimage.filters import convolve
from tkinter import *
import tkinter.filedialog
import threading

# 计算破坏度
def calc_d(img):
    filter_du = np.array([
        [1.0, 2.0, 1.0],
        [0.0, 0.0, 0.0],
        [-1.0, -2.0, -1.0],
    ])
    filter_du = np.stack([filter_du] * 3, axis=2)

    filter_dv = np.array([
        [1.0, 0.0, -1.0],
        [2.0, 0.0, -2.0],
        [1.0, 0.0, -1.0],
    ])
    filter_dv = np.stack([filter_dv] * 3, axis=2)

    img = img.astype('float32')
    convolved = np.absolute(convolve(img, filter_du)) + np.absolute(convolve(img, filter_dv))

    energy_map = convolved.sum(axis=2)

    return energy_map

# 搜索接缝
def search_seam(img):
    d=calc_d(img)
    m=d.shape[0]
    n=d.shape[1]
    e=[[float('inf') for i in range(n)] for i in range(m)]
    loc=[[-2 for i in range(n)] for j in range(m)]
    def min_point(i,j):
        if i==0:
            return 0,0
        a,b,c=0,e[i-1][j],0
        if j>0:
            a=e[i-1][j-1]
        else:
            a=float('inf')
        if j<n-1:
            c=e[i-1][j+1]
        else:
            c=float('inf')

        if a<c:
            if a<b:
                return a,-1
            else:
                return b,0
        else:
            if c<b:
                return c,1
            else:
                return b,0

    for i in range(m):
        for j in range(n):
            e_min, e_min_index=min_point(i,j)
            e[i][j]=d[i][j]+e_min
            if i>0:
                loc[i][j]=e_min_index

    min_index=np.argmin(e[-1])
    seam=[copy.copy(min_index)]
    for i in range(m-1, 0, -1):
        min_index=min_index+loc[i][min_index]
        seam.append(copy.copy(min_index))
    return seam

# 删除接缝
def carve_column(img):
    m, n, _ = img.shape

    mask = np.ones((m, n), dtype=np.bool)

    seam = search_seam(img)

    for i in range(m):
        mask[m-i-1][seam[i]]=False

    mask = np.stack([mask] * 3, axis=2)

    img = img[mask].reshape((m, n - 1, 3))

    return img

# 缩小列数
def crop_column(img, scale, t=False):
    m, n, _ = img.shape

    img_new=copy.copy(img)

    if t:
        for i in range(int(scale * n)):
            img_new=carve_column(img_new)
            text1.set('当前图片大小：%dx%d'%(img_new.shape[1],img_new.shape[0]))
    else:
        for i in range(int(scale * n)):
            img_new=carve_column(img_new)
            text1.set('当前图片大小：%dx%d'%(img_new.shape[0],img_new.shape[1]))

    return img_new

# 缩小行数
def crop_row(img, scale):
    img = np.rot90(img, 1, (0, 1))
    img = crop_column(img, scale, t=True)
    img = np.rot90(img, 3, (0, 1))
    return img

def op_img(path):
    img_0=mpimg.imread(path)
    text2.set('当前图片大小：%dx%d'%(img_0.shape[0],img_0.shape[1]))
    text2.set('预计图片大小：%dx%d'%(img_0.shape[0]-img_0.shape[0]//2,img_0.shape[1]-img_0.shape[1]//2))
    img_new=crop_column(img_0,0.5)
    img_new=crop_row(img_new,0.5)
    plt.subplot(1, 2, 1)
    plt.title('origin')
    plt.imshow(img_0)
    plt.subplot(1, 2, 2)
    plt.title('new')
    plt.imshow(img_new)
    plt.show(block=True)

def select():
    path = tkinter.filedialog.askopenfilename()
    if path != '':
        t=threading.Thread(target=op_img,args=(path,))
        t.setDaemon(True)
        t.start()

if __name__ == '__main__':
    window = Tk()
    window.title('Seam Carving Example')
    window.geometry("240x80")
    text1 = StringVar()
    text2 = StringVar()
    text1.set('当前图片大小：')
    text2.set('预计图片大小：')
    label1 = Label(window,textvariable=text1)
    label1.pack()
    label2 = Label(window,textvariable=text2)
    label2.pack()
    btn0 = Button(window,text="选择图片文件(.jpg)",command=select)
    btn0.pack()
    window.mainloop()