//
// Created by Artyom on 28.10.2023.
//

#ifndef DISCRETE_MATH_MATRIX_H
#define DISCRETE_MATH_MATRIX_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Структура описывающая матрицу
typedef struct Matrix {
    long long **values; // значения
    long long n_rows;   // кол-во строк
    long long n_cols;   // кол-во столбцов
} Matrix;

// Выделение памяти для матрицы a размера m * n
Matrix get_matrix(const long long n_rows, const long long n_cols);

// Освобождение памяти выделенной под матрицу
void free_matrix(Matrix a);

// Вывод матрицы a размера n * m
void output_matrix(Matrix a);

// Функция для проверки равенства двух матриц
int equality(Matrix *a, Matrix *b);

// Функция для проверки включения одной матрицы в другую
int inclusion(Matrix *a, Matrix *b);

// Функция для проверки строгого включения одной матрицы в другую
int strict_inclusion(Matrix *a, Matrix *b);

// Функция для объединения двух матриц
Matrix unification(Matrix *a, Matrix *b);

// Функция для пересечения двух матриц
Matrix intersection(Matrix *a, Matrix *b);

// Функция для разности двух матриц
Matrix difference(Matrix *a, Matrix *b);

// Функция для симметричной разности двух матриц
Matrix symmetric_difference(Matrix *a, Matrix *b);

// Функция для сложения двух матриц
Matrix addition(Matrix *a, Matrix *b);

// Функция для обращения A^-1
void appeal(Matrix *original_matrix, Matrix *matrix_for_operations);

// Функция для композиции
void composition(Matrix *matrix_1, Matrix *matrix_2, Matrix *matrix_for_operations);

// Функция для копирования матриц
Matrix copy_matrix(Matrix *original_matrix);

#endif //DISCRETE_MATH_MATRIX_H
