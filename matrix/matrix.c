//
// Created by Artyom on 28.10.2023.
//

#include "matrix.h"

Matrix get_matrix(const long long n_rows, const long long n_cols) {
    long long **a = (long long **) malloc(sizeof(long long *) * n_rows);

    for (size_t i = 0; i < n_rows; i++)
        a[i] = (long long *) malloc(sizeof(long long) * n_cols);

    Matrix matrix = {
            a,
            n_rows,
            n_cols
    };
    return matrix;
}

void free_matrix(Matrix a) {
    for (size_t i = 0; i < a.n_rows; i++)
        free(a.values[i]);

    free(a.values);
}

void output_matrix(Matrix a) {
    for (size_t i = 0; i < a.n_rows; i++) {
        for (size_t j = 0; j < a.n_cols; j++)
            printf("%lld ", a.values[i][j]);

        printf("\n");
    }

    printf("\n");
}

int equality(Matrix *a, Matrix *b) {
    if (a->n_rows != b->n_rows || a->n_cols != b->n_cols)
        return 0;

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++)
            if (a->values[i][j] != b->values[i][j])
                return 0;

    return 1;
}

int inclusion(Matrix *a, Matrix *b) {
    if (a->n_rows != b->n_rows || a->n_cols != b->n_cols)
        return 0;

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++)
            if (a->values[i][j] && !b->values[i][j])
                return 0;

    return 1;
}

int strict_inclusion(Matrix *a, Matrix *b) {
    if (a->n_rows != b->n_rows || a->n_cols != b->n_cols)
        return 0;

    int is_strict = 0;

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++) {
            if (a->values[i][j] && !b->values[i][j])
                return 0;

            if (!a->values[i][j] && b->values[i][j])
                is_strict = 1;
        }

    return is_strict;
}

Matrix unification(Matrix *a, Matrix *b) {
    assert(a->n_rows == b->n_rows && a->n_cols == b->n_cols);

    Matrix result = get_matrix(a->n_rows, a->n_cols);

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++)
            result.values[i][j] = a->values[i][j] || b->values[i][j];

    return result;
}

Matrix intersection(Matrix *a, Matrix *b) {
    assert(a->n_rows == b->n_rows && a->n_cols == b->n_cols);

    Matrix result = get_matrix(a->n_rows, a->n_cols);

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++)
            result.values[i][j] = a->values[i][j] && b->values[i][j];

    return result;
}

Matrix difference(Matrix *a, Matrix *b) {
    assert(a->n_rows == b->n_rows && a->n_cols == b->n_cols);

    Matrix result = get_matrix(a->n_rows, a->n_cols);

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++)
            result.values[i][j] = a->values[i][j] && !b->values[i][j];

    return result;
}

Matrix symmetric_difference(Matrix *a, Matrix *b) {
    assert(a->n_rows == b->n_rows && a->n_cols == b->n_cols);

    Matrix result = get_matrix(a->n_rows, a->n_cols);

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++)
            result.values[i][j] = a->values[i][j] ^ b->values[i][j];

    return result;
}

Matrix addition(Matrix *a, Matrix *b) {
    assert(a->n_rows == b->n_rows && a->n_cols == b->n_cols);

    Matrix result = get_matrix(a->n_rows, a->n_cols);

    for (long long i = 0; i < a->n_rows; i++)
        for (long long j = 0; j < a->n_cols; j++)
            result.values[i][j] = a->values[i][j] + b->values[i][j];

    return result;
}

void appeal(Matrix *original_matrix, Matrix *matrix_for_operations) {
    // Проверка на совместимость матриц
    assert(original_matrix->n_rows == matrix_for_operations->n_cols &&
        original_matrix->n_cols == matrix_for_operations->n_rows);

    for (long long x = 0; x < original_matrix->n_cols; x++)
        for (long long y = 0; y < original_matrix->n_rows; y++)
            matrix_for_operations->values[x][y] = original_matrix->values[y][x];
}

void composition(Matrix *matrix_1, Matrix *matrix_2, Matrix *matrix_for_operations) {
    // Проверка на совместимость матриц
    assert(matrix_1->n_cols == matrix_2->n_rows && matrix_1->n_rows == matrix_for_operations->n_rows &&
           matrix_2->n_cols == matrix_for_operations->n_cols);

    for (long long x = 0; x < matrix_1->n_rows; x++)
        for (long long y = 0; y < matrix_2->n_cols; y++) {
            matrix_for_operations->values[x][y] = 0;

            for (long long z = 0; z < matrix_1->n_cols; z++)
                if ((matrix_for_operations->values[x][y] || (matrix_1->values[x][z] &&
                                                             matrix_2->values[z][y])))
                    matrix_for_operations->values[x][y] = 1;
                else
                    matrix_for_operations->values[x][y] = 0;
        }
}

Matrix copy_matrix(Matrix *original_matrix) {
    // Создание новой матрицы
    Matrix new_matrix = get_matrix(original_matrix->n_cols, original_matrix->n_rows);

    new_matrix.n_rows = original_matrix->n_rows;
    new_matrix.n_cols = original_matrix->n_cols;
    new_matrix.values = malloc(new_matrix.n_rows * sizeof(long long *));

    for (long long i = 0; i < new_matrix.n_rows; i++) {
        new_matrix.values[i] = malloc(new_matrix.n_cols * sizeof(long long));

        for (long long j = 0; j < new_matrix.n_cols; j++)
            new_matrix.values[i][j] = original_matrix->values[i][j];
    }

    return new_matrix;
}