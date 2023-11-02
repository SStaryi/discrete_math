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

bool is_reflexive(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        if (matrix->values[i][i] != 1)
            return false;

    return true;
}

bool is_antireflexive(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        if (matrix->values[i][i] != 0)
            return false;

    return true;
}

bool is_symmetric(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            if (matrix->values[i][j] != matrix->values[j][i])
                return false;

    return true;
}

bool is_antisymmetric(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            if (i != j && matrix->values[i][j] == 1 && matrix->values[j][i] == 1)
                return false;

    return true;
}

bool is_transitive(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            for (long long k = 0; k < matrix->n_cols; k++)
                if (matrix->values[i][j] == 1 && matrix->values[j][k] == 1 && matrix->values[i][k] != 1)
                    return false;

    return true;
}

bool is_antitransitive(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            for (long long k = 0; k < matrix->n_cols; k++)
                if (matrix->values[i][j] == 1 && matrix->values[j][k] == 1 && matrix->values[i][k] == 1)
                    return false;

    return true;
}

bool is_connected(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            // Проверка связности
            if (i != j && matrix->values[i][j] == 0 && matrix->values[j][i] == 0)
                return 0;

    return 1;
}

bool is_complete(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            if (i != j && matrix->values[i][j] == 0)
                return 0;

    return 1;
}

bool is_tolerant(Matrix *matrix) {
    for (long long i = 0; i < matrix->n_rows; i++) {
        if (matrix->values[i][i] != 1)
            return 0;

        for (long long j = 0; j < matrix->n_cols; j++)
            if (i != j && matrix->values[i][j] != 0 && matrix->values[j][i] != 1)
                return 0;
    }

    return 1;
}

bool is_equivalent(Matrix *matrix) {
    return is_reflexive(matrix) && is_symmetric(matrix) && is_transitive(matrix);
}

bool is_order(Matrix *matrix) {
    return is_reflexive(matrix) && is_antisymmetric(matrix) && is_transitive(matrix);
}

bool is_strict_order(Matrix *matrix) {
    // Строгий порядок является антирефлексивным, антисимметричным и транзитивным
    return is_antireflexive(matrix) && is_antisymmetric(matrix) && is_transitive(matrix);
}

bool is_not_strict_order(Matrix *matrix) {
    // Не строгий порядок является рефлексивным, антисимметричным и транзитивным
    return is_reflexive(matrix) && is_antisymmetric(matrix) && is_transitive(matrix);
}

bool is_linear_order(Matrix *matrix) {
    return is_reflexive(matrix) && is_antisymmetric(matrix) && is_transitive(matrix) &&
           is_connected(matrix);
}

bool is_strict_linear_order(Matrix *matrix) {
    // Строгий линейный порядок является антирефлексивным, антисимметричным и транзитивным
    // и каждый элемент связан с каждым другим элементом
    if (!is_antireflexive(matrix) || !is_antisymmetric(matrix) || !is_transitive(matrix))
        return false;

    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            if (i != j && matrix->values[i][j] != 1 && matrix->values[j][i] != 1)
                return false;

    return true;
}

bool is_not_strict_linear_order(Matrix *matrix) {
    // Не строгий линейный порядок является рефлексивным, антисимметричным и транзитивным
    // и каждый элемент связан с каждым другим элементом
    if (!is_reflexive(matrix) || !is_antisymmetric(matrix) || !is_transitive(matrix))
        return false;

    for (long long i = 0; i < matrix->n_rows; i++)
        for (long long j = 0; j < matrix->n_cols; j++)
            if (i != j && matrix->values[i][j] != 1 && matrix->values[j][i] != 1)
                return false;

    return true;
}

void all_relationship_properties(Matrix *m) {
    printf("Reflexive: %d\n", is_reflexive(m));
    printf("Antireflexive: %d\n", is_antireflexive(m));
    printf("Symmetric: %d\n", is_symmetric(m));
    printf("Antisymmetric: %d\n", is_antisymmetric(m));
    printf("Transitive: %d\n", is_transitive(m));
    printf("Antitransitive: %d\n", is_antitransitive(m));
    printf("Connected: %d\n", is_connected(m));
    printf("Complete: %d\n", is_complete(m));
    printf("Tolerant: %d\n", is_tolerant(m));
    printf("Equivalent: %d\n", is_equivalent(m));
    printf("Order: %d\n", is_order(m));
    printf("Strict order: %d\n", is_strict_order(m));
    printf("Not strict order: %d\n", is_not_strict_order(m));
    printf("Linear order: %d\n", is_linear_order(m));
    printf("Strict linear order: %d\n", is_strict_linear_order(m));
    printf("Not strict linear order: %d\n", is_not_strict_linear_order(m));
}