#include <check.h>
#include <stdio.h>
#include "s21_matrix.h"
#include <limits.h>
#include <stdlib.h>
#include <math.h>

START_TEST(s21_create_matrix_test_1) {
    matrix_t arr = s21_create_matrix(1, 3);
    ck_assert(arr.columns == 3 && arr.rows == 1 && arr.matrix_type == ZERO_MATRIX &&
                arr.matrix[0][0] == 0 && arr.matrix[0][1] == 0 && arr.matrix[0][2] == 0);
    s21_remove_matrix(&arr);
}
END_TEST

START_TEST(s21_remove_matrix_test_1) {
    matrix_t arr = s21_create_matrix(1, 3);
    s21_remove_matrix(&arr);
    ck_assert(arr.columns == 0 && arr.rows == 0 && arr.matrix_type == ZERO_MATRIX && arr.matrix == NULL);
    //
    arr = s21_create_matrix(0, 0);
    s21_remove_matrix(&arr);
    ck_assert(arr.columns == 0 && arr.rows == 0 && arr.matrix_type == ZERO_MATRIX && arr.matrix == NULL);
    //
    arr = s21_create_matrix(0, 100);
    s21_remove_matrix(&arr);
    ck_assert(arr.columns == 0 && arr.rows == 0 && arr.matrix_type == ZERO_MATRIX && arr.matrix == NULL);
    //
    arr = s21_create_matrix(100, 0);
    s21_remove_matrix(&arr);
    ck_assert(arr.columns == 0 && arr.rows == 0 && arr.matrix_type == ZERO_MATRIX && arr.matrix == NULL);
}
END_TEST

START_TEST(s21_eq_matrix_test_1) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 1, 2, 3 },
                         { 4, 5, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ 1, 2, 3 },
                         { 4, 5, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 1, 2, 3 },
                         { 4, 7, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ 1, 2, 3 },
                         { 4, 5, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == FAILURE);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 1, 2 },
                         { 4, 7 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 1);
    double arr2[2][1] = {{ 1 },
                         { 4 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == FAILURE);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_4) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0, 0 },
                         { 0, 0 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 0, 0 },
                         { 0, 0 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_5) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 1, 0 },
                         { 0, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 1, 0 },
                         { 0, 1 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_6) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0.1234567, 1 },
                         {         1, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 0.1234567, 1 },
                         {         1, 1 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_7) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 0, 0, 0 },
                         { 0, 0, 0 },
                         { 0, 0, 0 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 0, 0 },
                         { 0, 0 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == FAILURE);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_8) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 1, 0, 0 },
                         { 0, 1, 0 },
                         { 0, 0, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 1, 0 },
                         { 0, 1 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == FAILURE);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_9) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0.12345673, 1 },
                         {         1, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 0.12345674, 1 },
                         {         1, 1 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_10) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0.12345671, 1 },
                         {         1, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 0.12345679, 1 },
                         {         1, 1 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_eq_matrix_test_11) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0.123456799, 1 },
                         {           1, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 0.123456700, 1 },
                         {           1, 1 }};
    writeMatrix(&A2, &arr2[0][0]);
    ck_assert(s21_eq_matrix(&A1, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
}
END_TEST

START_TEST(s21_sum_matrix_test_1) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 1, 2, 3 },
                         { 4, 7, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ 1, 2, 3 },
                         { 4, 5, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t A3 = s21_create_matrix(3, 3);
    double arr3[3][3] = {{ 2,  4, 6},
                         { 8,  12, 12},
                         { 14, 16, 18}};
    writeMatrix(&A3, &arr3[0][0]);
    matrix_t result = s21_sum_matrix(&A1, &A2);
    ck_assert(s21_eq_matrix(&result, &A3) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&A3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
    matrix_t A1 = s21_create_matrix(1, 2);
    double arr1[1][2] = {{ 1, 2 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(1, 2);
    double arr2[1][2] = {{ 1, 2 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t A3 = s21_create_matrix(1, 2);
    double arr3[1][2] = {{ 2,  4 }};
    writeMatrix(&A3, &arr3[0][0]);
    matrix_t result = s21_sum_matrix(&A1, &A2);
    ck_assert(s21_eq_matrix(&result, &A3) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&A3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
    matrix_t A1 = s21_create_matrix(0, 0);
    matrix_t A2 = s21_create_matrix(0, 0);
    matrix_t A3 = s21_create_matrix(0, 0);
    A3.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_sum_matrix(&A1, &A2);
    ck_assert(result.matrix_type == A3.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&A3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_1) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 1, 2, 3 },
                         { 4, 5, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ 1, 2, 3 },
                         { 4, 5, 6 },
                         { 7, 8, 9 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t A3 = s21_create_matrix(3, 3);
    double arr3[3][3] = {{ 0, 0, 0},
                         { 0, 0, 0},
                         { 0, 0, 0}};
    writeMatrix(&A3, &arr3[0][0]);
    matrix_t result = s21_sub_matrix(&A1, &A2);
    ck_assert(s21_eq_matrix(&result, &A3) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&A3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
    matrix_t A1 = s21_create_matrix(0, 0);
    matrix_t A2 = s21_create_matrix(0, 0);
    matrix_t A3 = s21_create_matrix(0, 0);
    A3.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_sub_matrix(&A1, &A2);
    ck_assert(result.matrix_type == A3.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&A3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_1) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 3, -1, 2 },
                         { 4,  2, 0 },
                         {-5,  6, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ 6,  -2, 4 },
                         { 8,   4, 0 },
                         {-10, 12, 2 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_mult_number(&A1, 2);
    ck_assert(s21_eq_matrix(&result, &A2));
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_2) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 3, -1, 2 },
                         { 4,  2, 0 },
                         {-5,  6, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ 0, 0, 0 },
                         { 0, 0, 0 },
                         { 0, 0, 0 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_mult_number(&A1, 0);
    ck_assert(s21_eq_matrix(&result, &A2));
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_3) {
    matrix_t A1 = s21_create_matrix(0, 0);
    matrix_t A2 = s21_create_matrix(3, 3);
    A2.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_mult_number(&A1, 0);
    ck_assert(result.matrix_type == A2.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_1) {
    double arr1[3][3] = {{ 3, -1, 2 },
                         { 4,  2, 0 },
                         {-5,  6, 1 }};
    matrix_t A1 = s21_create_matrix(3, 3);
    writeMatrix(&A1, &arr1[0][0]);
    double arr2[3][2] = {{ 8,  1 },
                         { 7,  2 },
                         { 2, -3 }};
    matrix_t A2 = s21_create_matrix(3, 2);
    writeMatrix(&A2, &arr2[0][0]);
    double arr3[3][2] = {{ 21, -5 },
                         { 46,  8 },
                         {  4,  4 }};
    matrix_t A3 = s21_create_matrix(3, 2);
    writeMatrix(&A3, &arr3[0][0]);
    matrix_t result = s21_mult_matrix(&A1, &A2);
    ck_assert(s21_eq_matrix(&result, &A3) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&A3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
    matrix_t A1 = s21_create_matrix(0, 0);
    matrix_t A2 = s21_create_matrix(0, 0);
    matrix_t A3 = s21_create_matrix(3, 2);
    A3.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_mult_matrix(&A1, &A2);
    ck_assert(result.matrix_type == A3.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&A3);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_matrix_test_1) {
    matrix_t A1 = s21_create_matrix(3, 2);
    double arr1[3][2] = {{ 3, -1 },
                         { 4,  2 },
                         {-5,  6 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 3);
    double arr2[2][3] = {{ 3, 4, -5 },
                         {-1, 2,  6 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_transpose(&A1);
    ck_assert(s21_eq_matrix(&result, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_matrix_test_2) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ -1,  38, -27 },
                         {  1, -41,  29 },
                         { -1,  34, -24 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ -1,   1,  -1 },
                         { 38, -41,  34 },
                         {-27,  29, -24 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_transpose(&A1);
    ck_assert(s21_eq_matrix(&result, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_matrix_test_3) {
    matrix_t A1 = s21_create_matrix(0, 0);
    matrix_t A2 = s21_create_matrix(2, 3);
    A2.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_transpose(&A1);
    ck_assert(result.matrix_type == A2.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_1) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 1, 2, 3 },
                         { 0, 4, 2 },
                         { 5, 2, 1 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{ 0,  10, -20 },
                         { 4, -14,   8 },
                         {-8,  -2,   4 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_calc_complements(&A1);
    ck_assert(s21_eq_matrix(&result, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_2) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0.3,   1.2 },
                         { 0.11, -1.7 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ -1.7,  -0.11 },
                         { -1.2, 0.3 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_calc_complements(&A1);
    ck_assert(s21_eq_matrix(&result, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_3) {
    matrix_t A1 = s21_create_matrix(0, 0);
    matrix_t A2 = s21_create_matrix(2, 2);
    A2.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_calc_complements(&A1);
    ck_assert(result.matrix_type == A2.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_4) {
    matrix_t A1 = s21_create_matrix(1, 1);
    matrix_t A2 = s21_create_matrix(1, 1);
    A2.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_calc_complements(&A1);
    ck_assert(result.matrix_type == A2.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_determinant_matrix_test_1) {
    matrix_t A1 = s21_create_matrix(1, 1);
    double arr1[1][1] = {{ 7 }};
    writeMatrix(&A1, &arr1[0][0]);
    ck_assert(7 == s21_determinant(&A1));
    s21_remove_matrix(&A1);
}
END_TEST

START_TEST(s21_determinant_matrix_test_2) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 7,  3},
                         { 3, -4}};
    writeMatrix(&A1, &arr1[0][0]);
    ck_assert(-37 == s21_determinant(&A1));
    s21_remove_matrix(&A1);
}
END_TEST

START_TEST(s21_determinant_matrix_test_3) {
    double arr1[3][3] = {{ 3, -1, 2 },
                         { 4,  2, 0 },
                         {-5,  6, 1 }};
    matrix_t A1 = s21_create_matrix(3, 3);
    writeMatrix(&A1, &arr1[0][0]);
    ck_assert(78 == s21_determinant(&A1));
    s21_remove_matrix(&A1);
}
END_TEST

START_TEST(s21_determinant_matrix_test_4) {
    double arr1[4][4] = {{ 3, -3, -5,  8 },
                         {-3,  2,  4, -6 },
                         { 2, -5, -7,  5 },
                         {-4,  3,  5, -6 }};
    matrix_t A1 = s21_create_matrix(4, 4);
    writeMatrix(&A1, &arr1[0][0]);
    ck_assert(18 == s21_determinant(&A1));
    s21_remove_matrix(&A1);
}
END_TEST

START_TEST(s21_determinant_matrix_test_5) {
    matrix_t A1 = s21_create_matrix(5, 5);
    double arr1[5][5] = {{ 3, -3, -5,  8, -9 },
                         {-3,  2,  4, -6,  7 },
                         { 2, -5, -7,  5,  2 },
                         {-4,  3,  5, -6,  3 },
                         {-2, 12, 11,  0,  4 }};
    writeMatrix(&A1, &arr1[0][0]);
    ck_assert(717 == s21_determinant(&A1));
    s21_remove_matrix(&A1);
}
END_TEST

START_TEST(s21_inverse_matrix_test_1) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 2,  5,  7 },
                         { 6,  3,  4 },
                         { 5, -2, -3 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{  1,  -1,   1 },
                         {-38,  41, -34 },
                         { 27, -29,  24 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_inverse_matrix(&A1);
    ck_assert(s21_eq_matrix(&result, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_2) {
    matrix_t A1 = s21_create_matrix(3, 3);
    double arr1[3][3] = {{ 4,  3, -7 },
                         { 9,  8,  1 },
                         { 2,  1, -3 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(3, 3);
    double arr2[3][3] = {{-25./36, 1./18,  59./36 },
                         { 29./36, 1./18, -67./36 },
                         { -7./36, 1./18,   5./36 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_inverse_matrix(&A1);
    ck_assert(s21_eq_matrix(&result, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_3) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0.7,  0.3 },
                         { 0.9,  0.44 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 220./19, -150./19 },
                         {-450./19, 350./19 }};
    writeMatrix(&A2, &arr2[0][0]);
    matrix_t result = s21_inverse_matrix(&A1);
    ck_assert(s21_eq_matrix(&result, &A2) == SUCCESS);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_4) {
    matrix_t A1 = s21_create_matrix(2, 2);
    double arr1[2][2] = {{ 0,  0 },
                         { 0,  0 }};
    writeMatrix(&A1, &arr1[0][0]);
    matrix_t A2 = s21_create_matrix(2, 2);
    double arr2[2][2] = {{ 1, 1 },
                         { 1, 1 }};
    writeMatrix(&A2, &arr2[0][0]);
    A2.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_inverse_matrix(&A1);
    ck_assert(result.matrix_type == A2.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_5) {
    matrix_t A1 = s21_create_matrix(0, 0);
    matrix_t A2 = s21_create_matrix(2, 2);
    A2.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_inverse_matrix(&A1);
    ck_assert(result.matrix_type == A2.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_6) {
    matrix_t A1 = s21_create_matrix(1, 1);
    matrix_t A2 = s21_create_matrix(1, 1);
    A2.matrix_type = INCORRECT_MATRIX;
    matrix_t result = s21_inverse_matrix(&A1);
    ck_assert(result.matrix_type == A2.matrix_type);
    s21_remove_matrix(&A1);
    s21_remove_matrix(&A2);
    s21_remove_matrix(&result);
}
END_TEST

int main(void) {
    // char *str = (char*)malloc(5);
    Suite *s1 = suite_create("Core");  // Объявляем сьюит
    SRunner *sr = srunner_create(s1);  // Лаунчер сьюита
    int failed_count;  // Статус тестов сьюита
    TCase *Case = tcase_create("Test");  // Новый кейс
    suite_add_tcase(s1, Case);  // Добавляем кейс

    tcase_add_test(Case, s21_create_matrix_test_1);

    tcase_add_test(Case, s21_remove_matrix_test_1);

    tcase_add_test(Case, s21_eq_matrix_test_1);
    tcase_add_test(Case, s21_eq_matrix_test_2);
    tcase_add_test(Case, s21_eq_matrix_test_3);
    tcase_add_test(Case, s21_eq_matrix_test_4);
    tcase_add_test(Case, s21_eq_matrix_test_5);
    tcase_add_test(Case, s21_eq_matrix_test_6);
    tcase_add_test(Case, s21_eq_matrix_test_7);
    tcase_add_test(Case, s21_eq_matrix_test_8);
    tcase_add_test(Case, s21_eq_matrix_test_9);
    tcase_add_test(Case, s21_eq_matrix_test_10);
    tcase_add_test(Case, s21_eq_matrix_test_11);

    tcase_add_test(Case, s21_sum_matrix_test_1);
    tcase_add_test(Case, s21_sum_matrix_test_2);
    tcase_add_test(Case, s21_sum_matrix_test_3);

    tcase_add_test(Case, s21_sub_matrix_test_1);
    tcase_add_test(Case, s21_sub_matrix_test_2);

    tcase_add_test(Case, s21_mult_number_test_1);
    tcase_add_test(Case, s21_mult_number_test_2);
    tcase_add_test(Case, s21_mult_number_test_3);

    tcase_add_test(Case, s21_mult_matrix_test_1);
    tcase_add_test(Case, s21_mult_matrix_test_2);

    tcase_add_test(Case, s21_transpose_matrix_test_1);
    tcase_add_test(Case, s21_transpose_matrix_test_2);
    tcase_add_test(Case, s21_transpose_matrix_test_3);

    tcase_add_test(Case, s21_calc_complements_test_1);
    tcase_add_test(Case, s21_calc_complements_test_2);
    tcase_add_test(Case, s21_calc_complements_test_3);
    tcase_add_test(Case, s21_calc_complements_test_4);

    tcase_add_test(Case, s21_determinant_matrix_test_1);
    tcase_add_test(Case, s21_determinant_matrix_test_2);
    tcase_add_test(Case, s21_determinant_matrix_test_3);
    tcase_add_test(Case, s21_determinant_matrix_test_4);
    tcase_add_test(Case, s21_determinant_matrix_test_5);

    tcase_add_test(Case, s21_inverse_matrix_test_1);
    tcase_add_test(Case, s21_inverse_matrix_test_2);
    tcase_add_test(Case, s21_inverse_matrix_test_3);
    tcase_add_test(Case, s21_inverse_matrix_test_4);
    tcase_add_test(Case, s21_inverse_matrix_test_5);
    tcase_add_test(Case, s21_inverse_matrix_test_6);

    srunner_run_all(sr, CK_ENV);
    failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);

    return 0;
}
