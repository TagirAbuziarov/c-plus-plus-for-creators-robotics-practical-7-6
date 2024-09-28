#include "c_api.h"
#include "src/matrix.h"

struct Matrix : public math::Matrix
{
public:
    Matrix(const struct math::Matrix &m) : math::Matrix(m) {};
};

Matrix *MATRIXLIB_EXPORT math_createMatrix(int rows, int columns)
{
    return new Matrix(math::Matrix(rows, columns));
}

void MATRIXLIB_EXPORT math_deleteMatrix(Matrix *m)
{
    delete m;
}

real MATRIXLIB_EXPORT math_matrix_get(const Matrix *m, int row, int column)
{
    return m->operator()(row, column);
}

void MATRIXLIB_EXPORT math_matrix_set(Matrix *m, int row, int column, real val)
{
    m->operator()(row, column) = val;
}

Matrix *MATRIXLIB_EXPORT math_matrix_add(const Matrix *m1, const Matrix *m2)
{
    return new Matrix(*m1 + *m2);
}

Matrix *MATRIXLIB_EXPORT math_matrix_substract(const Matrix *m1, const Matrix *m2)
{
    return new Matrix(*m1 - *m2);
}

Matrix *MATRIXLIB_EXPORT math_matrix_product(const Matrix *m1, const Matrix *m2)
{
    return new Matrix(*m1 * *m2);
}

void MATRIXLIB_EXPORT math_matrix_print(const Matrix *m)
{
    m->print();
}
