#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define Item(X, I, J, NCOL) X[((J) + (I) * (NCOL))]

extern void matmult(int *A, int *B, int *C, int l, int m, int n);
extern void matmult_v1(int *A, int *B, int *C, int l, int m, int n);
extern void matmult_v2(int *A, int *B, int *C, int l, int m, int n);
void populateMatrix(int *X, int nrow, int ncol);
void printMatrix(int *X, int nrow, int ncol);
int main()
{
    int l = 3, m = 4, n = 5;
    int *A = (int *)malloc(l * m * sizeof(int));
    int *B = (int *)malloc(m * n * sizeof(int));
    int *C = (int *)malloc(l * n * sizeof(int));

    populateMatrix(A, l, m);
    populateMatrix(B, m, n);

    matmult(A, B, C, l, m, n);

    printMatrix(A, l, m);
    printMatrix(B, m, n);
    printMatrix(C, l, n);

    matmult_v1(A, B, C, l, m, n);
    matmult_v2(A, B, C, l, m, n);

    free(A);
    free(B);
    free(C);

    return 0;
}
