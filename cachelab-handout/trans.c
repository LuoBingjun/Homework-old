// 骆炳君 软件71 2017013573
/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */

#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void trans(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int tmp, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
    // FILE *fp = fopen("demo.txt", "a+");
    // fprintf(fp, "%p", &A[0][1]);
    if (M == 32 && N == 32)
    {
        // 分为8*8的块
        for (r0 = 0; r0 < M / 8; r0++)
        {
            for (r1 = 0; r1 < N / 8; r1++)
            {
                for (r2 = 0; r2 < 8; r2++)
                {
                    for (r3 = 0; r3 < 8; r3++)
                    {
                        if (r0 * 8 + r2 != r1 * 8 + r3)
                        {
                            tmp = A[r0 * 8 + r2][r1 * 8 + r3];
                            B[r1 * 8 + r3][r0 * 8 + r2] = tmp;
                        }
                    }
                    // 单独处理对角线元素
                    if (r0 == r1)
                    {
                        tmp = A[r0 * 8 + r2][r0 * 8 + r2];
                        B[r0 * 8 + r2][r0 * 8 + r2] = tmp;
                    }
                }
            }
        }
    }
    else if (M == 64 && N == 64)
    {
        // 分成8*8的块
        for (r0 = 0; r0 < N; r0 += 8)
        {
            for (r1 = 0; r1 < M; r1 += 8)
            {
                for (r2 = r0; r2 < r0 + 4; r2++)
                {
                    // 逐行读A'的上半部分
                    r3 = A[r2][r1];
                    r4 = A[r2][r1 + 1];
                    r5 = A[r2][r1 + 2];
                    r6 = A[r2][r1 + 3];
                    r7 = A[r2][r1 + 4];
                    r8 = A[r2][r1 + 5];
                    r9 = A[r2][r1 + 6];
                    r10 = A[r2][r1 + 7];

                    // B'的左上部分直接存储转置结果
                    B[r1][r2] = r3;
                    B[r1 + 1][r2] = r4;
                    B[r1 + 2][r2] = r5;
                    B[r1 + 3][r2] = r6;

                    // B'的右上部分临时存储左下部分的数据
                    B[r1 + 3][r2 + 4] = r7;
                    B[r1 + 2][r2 + 4] = r8;
                    B[r1 + 1][r2 + 4] = r9;
                    B[r1][r2 + 4] = r10;
                }

                for (r2 = 0; r2 < 4; r2++)
                {
                    // 从两侧到中间按列读取A'的下半部分
                    r3 = A[r0 + 4][r1 + r2];
                    r4 = A[r0 + 5][r1 + r2];
                    r5 = A[r0 + 6][r1 + r2];
                    r6 = A[r0 + 7][r1 + r2];
                    r7 = A[r0 + 4][r1 + 7 - r2];
                    r8 = A[r0 + 5][r1 + 7 - r2];
                    r9 = A[r0 + 6][r1 + 7 - r2];
                    r10 = A[r0 + 7][r1 + 7 - r2];

                    // 把B'右上部分暂存的数据转移到左下部分
                    B[r1 + 7 - r2][r0] = B[r1 + r2][r0 + 4];
                    B[r1 + 7 - r2][r0 + 1] = B[r1 + r2][r0 + 5];
                    B[r1 + 7 - r2][r0 + 2] = B[r1 + r2][r0 + 6];
                    B[r1 + 7 - r2][r0 + 3] = B[r1 + r2][r0 + 7];

                    // B'左上部分写入正确数据
                    B[r1 + r2][r0 + 4] = r3;
                    B[r1 + r2][r0 + 5] = r4;
                    B[r1 + r2][r0 + 6] = r5;
                    B[r1 + r2][r0 + 7] = r6;

                    // B'右下部份直接存储转置结果
                    B[r1 + 7 - r2][r0 + 4] = r7;
                    B[r1 + 7 - r2][r0 + 5] = r8;
                    B[r1 + 7 - r2][r0 + 6] = r9;
                    B[r1 + 7 - r2][r0 + 7] = r10;
                }
            }
        }
    }
    else if (M == 61 && N == 67)
    {
        // 分为17*17的块
        for (r0 = 0; r0 < N; r0 += 17)
        {
            for (r1 = 0; r1 < M; r1 += 17)
            {
                for (r2 = r0; r2 < N && r2 < r0 + 17; r2++)
                {
                    for (r3 = r1; r3 < M && r3 < r1 + 17; r3++)
                    {
                        if (r2 != r3)
                        {
                            tmp = A[r2][r3];
                            B[r3][r2] = tmp;
                        }
                    }
                    // 单独处理对角线元素
                    if (r0 == r1)
                    {
                        tmp = A[r2][r2];
                        B[r2][r2] = tmp;
                    }
                }
            }
        }
    }
    else if (M == 48 && N == 48)
    {
        // 分为8*8的块
        for (r0 = 0; r0 < N; r0 += 8)
        {
            for (r1 = 0; r1 < M; r1 += 8)
            {
                // 逐行复制
                for (r2 = 0; r2 < 8; r2++)
                {
                    r3 = A[r0 + r2][r1];
                    r4 = A[r0 + r2][r1 + 1];
                    r5 = A[r0 + r2][r1 + 2];
                    r6 = A[r0 + r2][r1 + 3];
                    r7 = A[r0 + r2][r1 + 4];
                    r8 = A[r0 + r2][r1 + 5];
                    r9 = A[r0 + r2][r1 + 6];
                    r10 = A[r0 + r2][r1 + 7];

                    B[r1 + r2][r0] = r3;
                    B[r1 + r2][r0 + 1] = r4;
                    B[r1 + r2][r0 + 2] = r5;
                    B[r1 + r2][r0 + 3] = r6;
                    B[r1 + r2][r0 + 4] = r7;
                    B[r1 + r2][r0 + 5] = r8;
                    B[r1 + r2][r0 + 6] = r9;
                    B[r1 + r2][r0 + 7] = r10;
                }

                // 在B中进行转置
                for (r2 = 0; r2 < 8; r2++)
                {
                    for (r3 = r2 + 1; r3 < 8; r3++)
                    {
                        tmp = B[r1 + r3][r0 + r2];
                        B[r1 + r3][r0 + r2] = B[r1 + r2][r0 + r3];
                        B[r1 + r2][r0 + r3] = tmp;
                    }
                }
            }
        }
    }
    else
    {
        trans(M, N, A, B);
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
