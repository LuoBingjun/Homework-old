#include <stdio.h>

void initMatrix(int M, int N, int A[M][N])
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = i * 100 + j;
        }
    }
}

void printMatrix(int M, int N, int A[M][N])
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int A[16][16];
    int B[16][16] = {0};
    initMatrix(16, 16, A);
    int r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
    for (r0 = 0; r0 < 16; r0 += 8)
    {
        for (r1 = 0; r1 < 16; r1 += 8)
        {
            for (r2 = r0; r2 < r0 + 4; r2++)
            {
                r3 = A[r2][r1];
                r4 = A[r2][r1 + 1];
                r5 = A[r2][r1 + 2];
                r6 = A[r2][r1 + 3];
                r7 = A[r2][r1 + 4];
                r8 = A[r2][r1 + 5];
                r9 = A[r2][r1 + 6];
                r10 = A[r2][r1 + 7];
                B[r1][r2] = r3;
                B[r1][r2 + 4] = r7;
                B[r1 + 1][r2] = r4;
                B[r1 + 1][r2 + 4] = r8;
                B[r1 + 2][r2] = r5;
                B[r1 + 2][r2 + 4] = r9;
                B[r1 + 3][r2] = r6;
                B[r1 + 3][r2 + 4] = r10;
            }

            for (r2 = r0 + 4; r2 < r0 + 8; r2++)
            {
                r3 = A[r2][r1];
                r4 = A[r2][r1 + 1];
                r5 = A[r2][r1 + 2];
                r6 = A[r2][r1 + 3];
                r7 = A[r2][r1 + 4];
                r8 = A[r2][r1 + 5];
                r9 = A[r2][r1 + 6];
                r10 = A[r2][r1 + 7];
                B[r1 + 4][r2] = r7;
                B[r1 + 4][r2 - 4] = r3;
                B[r1 + 5][r2] = r8;
                B[r1 + 5][r2 - 4] = r4;
                B[r1 + 6][r2] = r9;
                B[r1 + 6][r2 - 4] = r5;
                B[r1 + 7][r2] = r10;
                B[r1 + 7][r2 - 4] = r6;
            }

            for (r2 = 0; r2 < 4; r2++)
            {
                r3 = B[r1 + r2][r0 + 4];
                r4 = B[r1 + r2][r0 + 5];
                r5 = B[r1 + r2][r0 + 6];
                r6 = B[r1 + r2][r0 + 7];
                B[r1 + r2][r0+ 4] = B[r1 + r2 + 4][r0+0];
                B[r1 + r2][r0+5] = B[r1 + r2 + 4][r0+1];
                B[r1 + r2][r0+6] = B[r1 + r2 + 4][r0+2];
                B[r1 + r2][r0+7] = B[r1 + r2 + 4][r0+3];
                B[r1 + r2 + 4][r0 + 0] = r3;
                B[r1 + r2 + 4][r0 + 1] = r4;
                B[r1 + r2 + 4][r0 + 2] = r5;
                B[r1 + r2 + 4][r0 + 3] = r6;
            }
        }
    }
    printMatrix(16, 16, A);
    printf("\n");
    printMatrix(16, 16, B);
    return 0;
}