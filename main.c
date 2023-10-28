#include <stdio.h>

#include "lab3_1/lab3_1.h"
#include "matrix/matrix.h"

int main() {
    long long size = 10;

    Matrix a = get_matrix(size, size);
    matrix_a(a);
    printf("Matrix A\n");
    output_matrix(a);

    Matrix b = get_matrix(size, size);
    matrix_b(b);
    printf("Matrix B\n");
    output_matrix(b);

    Matrix c = get_matrix(size, size);
    matrix_c(c);
    printf("Matrix C\n");
    output_matrix(c);

    Matrix d = get_matrix(size, size);
    matrix_d(a, b, c, &d);
    printf("Matrix D\n");
    output_matrix(d);

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
    free_matrix(d);

    return 0;
}
