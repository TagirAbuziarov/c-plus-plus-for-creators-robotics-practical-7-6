#pragma once
#include <vector>
#include <iostream>

namespace math
{
    class Matrix
    {
    private:
        int rows_number_;
        int columns_number_;
        std::vector<double> elements_vector_;
    
        /*
        Возвращает индекс элемента матрицы строки row и столбце column в 
        векторе elements_vector_. Если row или column вне границ матрицы, 
        вызывает исключение
        */
        int convertRowColumnToIndex_(int row, int column) const;

    public:
        Matrix();

        Matrix(int rows, int colums);

        ~Matrix();

        // Возвращает True, если матрицы a и b одинаковых размеров
        static bool isEqualSize(const Matrix &a, const Matrix &b);

        // Возвращает True, если матрицу a можно умножить на матрицу b
        static bool canBeMultiplied(const Matrix &a, const Matrix &b);

        // Вывод матрицы в std::cout
        void print() const;

        // Обеспечивает доступ к элементами матрицы
        double& operator()(int row, int column);

        /*
        Обеспечивает доступ к элементам матрицы, предоставленной по 
        const указателю или ссылке
        */
        double operator()(int row, int column) const;

        Matrix& operator+=(const Matrix &a);

        Matrix& operator-=(const Matrix &a);

        Matrix& operator*=(const Matrix &a);

        friend Matrix operator+(const Matrix &a, const Matrix &b);

        friend Matrix operator-(const Matrix &a, const Matrix &b);

        friend Matrix operator*(const Matrix &a, const Matrix &b);

        friend std::ostream& operator<<(std::ostream &cout, const Matrix &m);

        friend std::istream& operator>>(std::istream &cin, Matrix &m);
    };
}