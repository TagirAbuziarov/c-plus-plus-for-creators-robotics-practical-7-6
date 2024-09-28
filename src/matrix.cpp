#include <src/matrix.h>
#include <stdexcept>


namespace math
{
    Matrix::Matrix() : rows_number_(0), columns_number_(0) {}

    Matrix::Matrix(int rows, int columns)
    {
        /*
        Допускается создание либо пустой матрицы, либо матрицы, число как
        столбцов, так и строк которой являются натуральными числами
        */
        if (!(rows == 0 && columns == 0) && (rows <= 0 || columns <= 0))
        {
            throw std::range_error("Matrix: incorrect matrix size");
        }

        // Сохранение размеров матрицы
        this->rows_number_ = rows;
        this->columns_number_ = columns;

        // Выделение памяти под элементы матрицы
        int size = rows * columns;
        this->elements_vector_.resize(size, 0.);
    }

    Matrix::~Matrix() = default;

    bool Matrix::isEqualSize(const Matrix &a, const Matrix &b)
    {
        return a.columns_number_ == b.columns_number_ && a.rows_number_ == b.rows_number_;
    }

    bool Matrix::canBeMultiplied(const Matrix &a, const Matrix &b)
    {
        return a.columns_number_ == b.rows_number_;
    }

    int Matrix::convertRowColumnToIndex_(int row, int column) const
    {   
        // Проверка аргументов
        if (row < 0 || row >= this->rows_number_)
        {
            throw std::range_error("Matrix: row is out of bounds");
        }
        if (column < 0 || column >= this->columns_number_)
        {
            throw std::range_error("Matrix: column is out of bounds");
        }

        return columns_number_ * row + column;
    }

    void Matrix::print() const
    {
        std::cout << *this;
    }

    double &Matrix::operator()(int row, int column)
    {
        // Проверка аргументов
        // Вычисление индекса элемента в одномерном массиве
        int index {this->convertRowColumnToIndex_(row, column)};

        return this->elements_vector_.at(index);
    }

    double Matrix::operator()(int row, int column) const
    {
        // Проверка аргументов
        // Вычисление индекса элемента в одномерном массиве
        int index {this->convertRowColumnToIndex_(row, column)};

        return this->elements_vector_.at(index);
    }

    Matrix& Matrix::operator+=(const Matrix &a)
    {
        if (!Matrix::isEqualSize(*this, a))
        {
            throw std::range_error("Matrix: matrices cannot be summed");
        }

        for (int i = 0; i < this->elements_vector_.size(); i++)
        {
            this->elements_vector_.at(i) += a.elements_vector_.at(i);
        }

        return *this;
    }

    Matrix& Matrix::operator-=(const Matrix &a)
    {
        // Проверка аргументов
        if (!Matrix::isEqualSize(*this, a))
        {
            throw std::range_error("Matrix: matrices cannot be summed");
        }

        for (int i = 0; i < this->elements_vector_.size(); i++)
        {
            this->elements_vector_.at(i) -= a.elements_vector_.at(i);
        }

        return *this;
    }

    Matrix& Matrix::operator*=(const Matrix &a)
    {
        // Проверка аргументов
        if (!Matrix::canBeMultiplied(*this, a))
        {
            throw std::range_error("Matrix: matrices cannot be multiplied");
        }

        *this = *this * a;

        return *this;
    }

    Matrix operator+(const Matrix &a, const Matrix &b)
    {
        // Проверка аргументов
        if (!Matrix::isEqualSize(a, b))
        {
            throw std::range_error("Matrix: matrices cannot be summed");
        }

        Matrix m(a.rows_number_, a.columns_number_);

        // Проход по элементам результирующей матрицы
        for (int i = 0; i < m.elements_vector_.size(); i++)
        {
            m.elements_vector_.at(i) = a.elements_vector_.at(i) + b.elements_vector_.at(i);
        }

        return m;
    }

    Matrix operator-(const Matrix &a, const Matrix &b)
    {
        // Проверка аргументов
        if (!Matrix::isEqualSize(a, b))
        {
            throw std::range_error("Matrix: matrices cannot be summed");
        }

        Matrix m(a.rows_number_, a.columns_number_);

        // Проход по элементам результирующей матрицы
        for (int i = 0; i < m.elements_vector_.size(); i++)
        {
            m.elements_vector_.at(i) = a.elements_vector_.at(i) - b.elements_vector_.at(i);
        }

        return m;
    }

    Matrix operator*(const Matrix &a, const Matrix &b)
    {
        // Проверка аргументов
        if (!Matrix::canBeMultiplied(a, b))
        {
            throw std::range_error("Matrix: matrices cannot be multiplied");
        }

        // Инициализация результирующей матрицы
        Matrix m(a.rows_number_, b.columns_number_);

        // Проход по элементам результирующей матрицы
        for (int index = 0; index < m.elements_vector_.size(); index++)
        {
            // Вычисление строки и столбца элемента результирующей матрицы
            int row     {index / m.columns_number_};
            int column  {index - row * m.columns_number_};

            m.elements_vector_.at(index) = 0;

            // Вычисление значения элементов результирующей матрицы
            for (int k = 0; k < a.columns_number_; k++)
            {
                m.elements_vector_.at(index) += a(row, k) * b(k, column);
            }
        }

        return m;
    }

    std::ostream& operator<<(std::ostream& cout, const Matrix &m)
    {
        for (int row = 0; row < m.rows_number_; row++)
        {
            for (int column = 0; column < m.columns_number_; column++)
            {
                int index = m.columns_number_ * row + column;
                cout << m.elements_vector_.at(index) << " ";
            }
            cout << "\n";
        }
        return cout;
    }

    std::istream& operator>>(std::istream& cin, Matrix &m)
    {
        int rows{0}, columns{0};

        std::cout << "Создание матрицы. Введите число строк: ";
        cin >> rows;

        std::cout << "Создание матрицы. Введите число столбцов: ";
        cin >> columns;

        m = Matrix(rows, columns);

        for (int index = 0; index < m.elements_vector_.size(); index++)
        {
            // Вычисление позиции элемента с индексом index
            int row     {index / m.columns_number_};
            int column  {index - row * m.columns_number_};

            std::cout   << "Создание матрицы: введите элемент [" << row <<
                        "][" << column << "]: ";

            cin >> m.elements_vector_.at(index);
        }
        std::cout << "Матрица создана. Полученная матрица:\n" << m;
        
        return cin;        
    }
}