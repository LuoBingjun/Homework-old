import copy
import tkinter
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
from scipy.ndimage.filters import convolve

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

def carve_column(img):
    m, n, _ = img.shape

    # 创建一个(r,c)矩阵，填充值为True
    # 后面会从值为False的图像中移除所有像素
    mask = np.ones((m, n), dtype=np.bool)

    seam = search_seam(img)

    for i in range(m):
        mask[m-i-1][seam[i]]=False

    # 因为图像有3个通道，我们将蒙版转换为3D
    mask = np.stack([mask] * 3, axis=2)

    # 删除蒙版中所有标记为False的像素，
    # 将其大小重新调整为新图像的维度
    img = img[mask].reshape((m, n - 1, 3))

    return img

def crop_column(img, scale):
    m, n, _ = img.shape

    img_new=copy.copy(img)

    for i in range(int(scale * n)):
        print(i)
        img_new=carve_column(img_new)
        print(img_new.shape[0],img_new.shape[1])

    return img_new


def crop_row(img, scale):
    img = np.rot90(img, 1, (0, 1))
    img = crop_column(img, scale)
    img = np.rot90(img, 3, (0, 1))
    return img

img_0=mpimg.imread('sample.jpg')
img_new=crop_column(img_0,0.5)
img_new=crop_row(img_new,0.5)
plt.imshow(img_new)
plt.axis('off')
plt.show()
