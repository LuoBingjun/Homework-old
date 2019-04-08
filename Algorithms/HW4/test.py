import random

def PARTITION(A, p, r):
    x = A[r]
    i = p-1
    j = p-1
    for k in range(p, r+1):
        if A[k] < x:
            i = i+1
            j = j+1
            A[k], A[j] = A[j], A[k]
            A[j], A[i] = A[i], A[j]
        elif A[k] == x:
            j = j+1
            A[k], A[j] = A[j], A[k]
    return i+1, j


def RANDOMIZED_PARTITON(A, p, r):
    i = random.randint(p, r)
    A[r], A[i] = A[i], A[r]
    return PARTITION(A, p, r)


def RANDOMIZED_QUICKSORT(A, p, r):
    if p < r:
        q, t = RANDOMIZED_PARTITON(A, p, r)
        RANDOMIZED_QUICKSORT(A, p, q - 1)
        RANDOMIZED_QUICKSORT(A, t + 1, r)


def QUICKSORT(A, p, r):
    if p < r:
        q, t = RANDOMIZED_PARTITON(A, p, r)
        if p < q:
            RANDOMIZED_QUICKSORT(A, p, q - 1)
        if t < r:
            RANDOMIZED_QUICKSORT(A, t + 1, r)
