#include "libs/matrixlib/export_shared.h"
#include <iostream>
struct Matrix;

#ifdef __cplusplus
extern "C"
{
#endif

    typedef double real;

    extern Matrix *MATRIXLIB_EXPORT math_createMatrix(int rows, int columns);

    extern void MATRIXLIB_EXPORT math_deleteMatrix(Matrix *m);

    extern real MATRIXLIB_EXPORT math_matrix_get(const Matrix *m, int row, int column);

    extern void MATRIXLIB_EXPORT math_matrix_set(Matrix *m, int row, int column, real val);

    extern Matrix *MATRIXLIB_EXPORT math_matrix_add(const Matrix *m1, const Matrix *m2);

    extern Matrix *MATRIXLIB_EXPORT math_matrix_substract(const Matrix *m1, const Matrix *m2);

    extern Matrix *MATRIXLIB_EXPORT math_matrix_product(const Matrix *m1, const Matrix *m2);

    extern void MATRIXLIB_EXPORT math_matrix_print(const Matrix *M);


#ifdef __cplusplus
}
#endif

int main()
{
    // Динамическое выделение памяти под матрицы
    Matrix* m1 = math_createMatrix(3, 3);
    Matrix* m2 = math_createMatrix(3, 3);

    // Установка первых двух элементов главной диагонали
    math_matrix_set(m1, 0, 0, 3.0);
    math_matrix_set(m1, 1, 1, 3.0);
    math_matrix_set(m2, 0, 0, 5.0);
    math_matrix_set(m2, 1, 1, 5.0);

    std::cout << "Матрица m1:\n";
    math_matrix_print(m1);

    std::cout << "Матрица m2:\n";
    math_matrix_print(m2);
    
    std::cout << "m1+m2 =\n";
    Matrix* m3 = math_matrix_add(m1, m2);
    math_matrix_print(m3);

    std::cout << "m1-m2 =\n";
    Matrix* m4 = math_matrix_substract(m1, m2);
    math_matrix_print(m4);

    std::cout << "m1*m2 =\n";
    Matrix* m5 = math_matrix_product(m1, m2);
    math_matrix_print(m5);

    // Освобождение памяти, выделенной под матрицы
    math_deleteMatrix(m1);
    math_deleteMatrix(m2);
    math_deleteMatrix(m3);
    math_deleteMatrix(m4);
    math_deleteMatrix(m5);
}