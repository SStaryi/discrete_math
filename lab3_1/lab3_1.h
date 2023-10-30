//
// Created by Artyom on 26.10.2023.
//

#ifndef DISCRETE_MATH_LAB3_1_H
#define DISCRETE_MATH_LAB3_1_H

#include <stdbool.h>

#include "../matrix/matrix.h"

void matrix_a(Matrix a);

void matrix_b(Matrix b);

void matrix_c(Matrix c);

void matrix_d(Matrix a, Matrix b, Matrix c, Matrix *d);

// Функция для проверки рефлексивности матрицы
bool is_reflexive(Matrix *matrix);

// Функция для проверки симметричности матрицы
bool is_symmetric(Matrix *matrix);

// Функция для проверки транзитивности матрицы
bool is_transitive(Matrix *matrix);

// Функция для проверки свойства связности
bool is_connected(Matrix *matrix);

// Функция для проверки полноты матрицы
bool is_complete(Matrix *matrix);

// Функция для проверки толерантности матрицы
bool is_tolerant(Matrix *matrix);

// Функция для проверки эквивалентности матрицы
bool is_equivalent(Matrix *matrix);

// Функция для проверки свойства отношения порядка
bool is_order(Matrix *matrix);

// Функция для проверки свойства строгого порядка
bool is_strict_order(Matrix *matrix);

// Функция для проверки свойства линейного порядка
bool is_linear_order(Matrix *matrix);

// Функция для проверки свойства строгого линейного порядка
bool is_strict_linear_order(Matrix *matrix);

void all_relationship_properties(Matrix *m);

#endif //DISCRETE_MATH_LAB3_1_H
