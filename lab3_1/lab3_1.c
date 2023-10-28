//
// Created by Artyom on 26.10.2023.
//

#include "lab3_1.h"

void matrix_a(Matrix a) {
    for (long long x = 0; x < a.n_cols; x++)
        for (long long y = 0; y < a.n_rows; y++)
            a.values[x][y] = !(((x + 1) + (y + 1)) % 3) ? 1 : 0;
}

void matrix_b(Matrix b) {
    for (long long x = 0; x < b.n_cols; x++)
        for (long long y = 0; y < b.n_rows; y++)
            b.values[x][y] = (2 < (x + 1) && (x + 1) < 8) || (2 < (y + 1) && (y + 1) < 8) ? 1 : 0;
}

void matrix_c(Matrix c) {
    for (long long x = 0; x < c.n_cols; x++)
        for (long long y = 0; y < c.n_rows; y++)
            c.values[x][y] = ((x + 1) * (x + 1) + (y + 1) * (y + 1)) < 100 ? 1 : 0;
}

void matrix_d(Matrix a, Matrix b, Matrix c, Matrix *d) {
    Matrix new_a1 = copy_matrix(&a);
    Matrix new_b1 = copy_matrix(&b);
    Matrix a_2 = intersection(&new_a1, &new_b1);

    Matrix new_a2 = copy_matrix(&a);
    Matrix a_1 = get_matrix(a.n_cols, a.n_rows);
    appeal(&new_a2, &a_1);


    Matrix new_b2 = copy_matrix(&b);
    Matrix a_2_b = difference(&a_2, &new_b2);

    Matrix new_c1 = copy_matrix(&c);
    Matrix a_1_o_c = get_matrix(a.n_rows, a.n_cols);
    composition(&a_1, &new_c1, &a_1_o_c);

    *d = unification(&a_2_b, &a_1_o_c);

    free_matrix(new_a1);
    free_matrix(new_b1);
    free_matrix(new_a2);
    free_matrix(new_b2);
    free_matrix(new_c1);
}

// Функция для проверки рефлексивности матрицы
bool isReflexive(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++) {
        if (matrix->values[i][i] != 1) {
            return 0;
        }
    }
    return 1;
}

// Функция для проверки симметричности матрицы
bool isSymmetric(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++) {
        for (long long j = 0; j < matrix->n_cols; j++) {
            if (matrix->values[i][j] != matrix->values[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

// Функция для проверки транзитивности матрицы
bool isTransitive(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++) {
        for (long long j = 0; j < matrix->n_cols; j++) {
            for (long long k = 0; k < matrix->n_cols; k++) {
                if (matrix->values[i][j] && matrix->values[j][k] && !matrix->values[i][k]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

// Функция для проверки полноты матрицы
bool isComplete(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++) {
        for (long long j = 0; j < matrix->n_cols; j++) {
            if (i != j && matrix->values[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// Функция для проверки толерантности матрицы
bool isTolerant(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++) {
        if (matrix->values[i][i] != 1) {
            return 0;
        }
        for (long long j = 0; j < matrix->n_cols; j++) {
            if (i != j && matrix->values[i][j] != 0 && matrix->values[j][i] != 1) {
                return 0;
            }
        }
    }
    return 1;
}

// Функция для проверки эквивалентности матрицы
bool isEquivalent(Matrix *matrix) {
    return isReflexive(matrix) && isSymmetric(matrix) && isTransitive(matrix);
}

