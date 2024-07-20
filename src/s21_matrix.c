#include <stdio.h>
#include <stdlib.h>
#include "s21_matrix.h"
#include <math.h>

#define EPSILON (1e-7)

void writeType(matrix_t *a) {
    int unit = 1;
    int zero = 1;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->columns; j++) {
            if (a->matrix[i][j] != 0)
                zero = 0;
            if (i == j && a->matrix[i][j] != 1)
                unit = 0;
        }
    }
    if (zero == 1 || a->columns == 0 || a->rows == 0) {
        a->matrix_type = ZERO_MATRIX;
    } else if (unit == 1 && a->rows == a->columns) {
        a->matrix_type = IDENTITY_MATRIX;
    } else {
        a->matrix_type = CORRECT_MATRIX;
    }
}

void writeMatrix(matrix_t *a, double *_matrix) {
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->columns; j++) {
            a->matrix[i][j] = *(_matrix + i * a->columns + j);
        }
    }
    writeType(a);
}

matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t arr;
    arr.matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        arr.matrix[i] = (double*)malloc(columns * sizeof(double));
        for (int j = 0; j < columns; j++)
            arr.matrix[i][j] = 0;
    }
    arr.rows = rows;
    arr.columns = columns;
    arr.matrix_type = ZERO_MATRIX;

    return arr;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
    A->matrix_type = ZERO_MATRIX;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int value = FAILURE;
    if (A->matrix_type != INCORRECT_MATRIX && B->matrix_type != INCORRECT_MATRIX) {
        if (A->rows == B->rows && A->columns == B->columns) {
            value = SUCCESS;
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    if (!(fabs(A->matrix[i][j] - B->matrix[i][j]) < EPSILON))
                        value = FAILURE;
                }
            }
        } else {
            value = FAILURE;
        }
    }

    return value;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
    matrix_t arr = s21_create_matrix(A->rows, A->columns);
    if (A->rows == B->rows && A->columns == B->columns &&
        A->columns != 0 && A->rows != 0 && B->columns != 0 && B->rows != 0 &&
        A->matrix_type != INCORRECT_MATRIX && B->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                arr.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
        writeType(&arr);
    } else {
        arr.matrix_type = INCORRECT_MATRIX;
    }

    return arr;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    matrix_t arr = s21_create_matrix(A->rows, A->columns);
    if (A->rows == B->rows && A->columns == B->columns &&
        A->columns != 0 && A->rows != 0 && B->columns != 0 && B->rows != 0 &&
        A->matrix_type != INCORRECT_MATRIX && B->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                arr.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
        writeType(&arr);
    } else {
        arr.matrix_type = INCORRECT_MATRIX;
    }

    return arr;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
    matrix_t arr = s21_create_matrix(A->rows, A->columns);
    if (A->columns != 0 && A->rows != 0 && A->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                arr.matrix[i][j] = A->matrix[i][j] * number;
            }
        }
        writeType(&arr);
    } else {
        arr.matrix_type = INCORRECT_MATRIX;
    }

    return arr;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t arr = s21_create_matrix(A->rows, B->columns);
    if (A->columns == B->rows && A->columns != 0 && A->rows != 0 && B->columns != 0 && B->rows != 0
         && A->matrix_type != INCORRECT_MATRIX && B->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++) {
                    arr.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
        writeType(&arr);
    } else {
        arr.matrix_type = INCORRECT_MATRIX;
    }

    return arr;
}

matrix_t s21_transpose(matrix_t *A) {
    matrix_t arr = s21_create_matrix(A->columns, A->rows);
    if (A->columns != 0 && A->rows != 0 && A->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                arr.matrix[j][i] = A->matrix[i][j];
            }
        }
        writeType(&arr);
    } else {
        arr.matrix_type = INCORRECT_MATRIX;
    }
    return arr;
}

matrix_t s21_calc_complements(matrix_t *A) {
    matrix_t retArr = s21_create_matrix(A->rows, A->columns);
    if (A->columns == A->rows && A->columns != 0 && A->columns != 1 && A->matrix_type != INCORRECT_MATRIX) {
        matrix_t arr = s21_create_matrix(A->rows - 1, A->columns - 1);
        double matrixArr[A -> rows - 1][A -> columns - 1];
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                int tempN = 0;
                for (int n = 0; n < A->rows; n++) {
                    int tempM = 0;
                    for (int m = 0; m < A->columns; m++) {
                        if (m == j) {
                            tempM = 1;
                        } else if (n == i) {
                            tempN = 1;
                        } else {
                            matrixArr[n - tempN][m - tempM] = A->matrix[n][m];
                        }
                    }
                }
                writeMatrix(&arr, &matrixArr[0][0]);
                retArr.matrix[i][j] = pow(-1, i + j) * s21_determinant(&arr);
            }
        }
        writeType(&retArr);
        s21_remove_matrix(&arr);
    } else {
        retArr.matrix_type = INCORRECT_MATRIX;
    }
    return retArr;
}

double s21_determinant(matrix_t *A) {
    double x = 0;
    if (A->columns == A->rows && A->columns != 0 && A->matrix_type != INCORRECT_MATRIX) {
        if (A -> rows > 2) {
            matrix_t arr = s21_create_matrix(A->rows - 1, A->columns - 1);
            double matrixArr[A -> rows - 1][A -> columns - 1];
            for (int i = 0; i < A->columns; i++) {
                for (int j = 1; j < A -> rows; j++) {
                    int temp = 0;
                    for (int k = 0; k < A -> columns; k++) {
                        if (i == k) {
                            temp = 1;
                        } else {
                            matrixArr[j - 1][k - temp] = A->matrix[j][k];
                        }
                    }
                }
                writeMatrix(&arr, &matrixArr[0][0]);
                x += pow(-1, i) * A -> matrix[0][i] * s21_determinant(&arr);
            }
            s21_remove_matrix(&arr);
        } else if (A->rows == 2) {
            x += A -> matrix[0][0] * A -> matrix[1][1] - A -> matrix[0][1] * A -> matrix[1][0];
        } else if (A -> rows == 1) {
            x += A -> matrix[0][0];
        }
    } else {
        x = NAN;
    }
    return x;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
    matrix_t returnMatrix = s21_create_matrix(0, 0);
    if (A->rows == A->columns && A->matrix_type != INCORRECT_MATRIX && A->columns != 0 && A->columns != 1) {
        double x = s21_determinant(A);
        if (x != 0) {
            s21_remove_matrix(&returnMatrix);
            matrix_t matr = s21_calc_complements(A);
            returnMatrix = s21_transpose(&matr);
            s21_remove_matrix(&matr);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    returnMatrix.matrix[i][j] = returnMatrix.matrix[i][j] / x;
                }
            }
            writeType(&returnMatrix);
        } else {
            returnMatrix.matrix_type = INCORRECT_MATRIX;
        }
    } else {
        returnMatrix.matrix_type = INCORRECT_MATRIX;
    }

    return returnMatrix;
}
