#pragma once
#include "src/export.h"

typedef double real;

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Matrix Matrix;

    Matrix *MATRIXLIB_EXPORT math_createMatrix(int rows, int columns);

    void MATRIXLIB_EXPORT math_deleteMatrix(Matrix *m);

    real MATRIXLIB_EXPORT math_matrix_get(const Matrix *m, int row, int column);

    void MATRIXLIB_EXPORT math_matrix_set(Matrix *m, int row, int column, real val);

    Matrix *MATRIXLIB_EXPORT math_matrix_add(const Matrix *m1, const Matrix *m2);

    Matrix *MATRIXLIB_EXPORT math_matrix_substract(const Matrix *m1, const Matrix *m2);

    Matrix *MATRIXLIB_EXPORT math_matrix_product(const Matrix *m1, const Matrix *m2);

    void MATRIXLIB_EXPORT math_matrix_print(const Matrix *M);

#ifdef __cplusplus
}
#endif