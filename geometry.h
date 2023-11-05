#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

#include "print.h"

template <typename T, typename U>
T dot(std::vector<T> &lhs, std::vector<U> &rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::length_error("vector lhs and vector rhs should be of same size");
    }

    T r = 0;

    for (size_t i = 0; i != lhs.size(); i++) {
        r += lhs[i] * rhs[i];
    }

    return r;
}

template <typename T>
class Matrix;

template <typename T>
class Vec2;

template <typename T>
class Vec3;

template <typename T>
class Vec4;

// Matrix
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> m;

public:
    size_t rows;
    size_t cols;

    Matrix(): m(1, std::vector<T>(1, 0)), rows(1), cols(1) {}

    Matrix(size_t size): m(size, std::vector<T>(size)), rows(size), cols(size) {
        for (int i = 0; i != size; i++) {
            m[i][i] = 1;
        }
    }

    Matrix(size_t rows, size_t cols): m(rows, std::vector<T>(cols, 0)), rows(rows), cols(cols) {}

    Matrix(size_t rows, size_t cols, T n): m(rows, std::vector<T>(cols, n)), rows(rows), cols(cols) {}

    Matrix(T* v, size_t s): m(1, std::vector<T>(v, v + s)), rows(1), cols(s) {}

    template <size_t S>
    Matrix(std::array<T, S> &v): m(1, std::vector<T>(v.begin(), v.end())), rows(1), cols(v.size()) {}

    Matrix(std::initializer_list<T> v): m(1, std::vector<T>(v.begin(), v.end())), rows(1), cols(v.size()) {}

    template <size_t C>
    Matrix(T v[][C], size_t rows, size_t cols): m(rows, std::vector<T>(cols)), rows(rows), cols(cols) {
        for (size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[i][j] = v[i][j];
            }
        }
    }

    template <size_t R, size_t C>
    Matrix(std::array<std::array<T, C>, R> &v): m(R, std::vector<T>(C)), rows(v.size()), cols(v.begin()->size()) {
        for (size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[i][j] = v[i][j];
            }
        }
    }

    Matrix(Vec2<T> &v);
    Matrix(Vec3<T> &v);
    Matrix(Vec4<T> &v);

    Matrix(std::initializer_list<std::initializer_list<T>> v): 
        m(v.size(), std::vector<T>(v.begin()->size())), 
        rows(v.size()), 
        cols(v.begin()->size()) 
    {
        for (size_t i = 0; i != v.size(); i++) {
            for (size_t j = 0; j != v.begin()->size(); j++) {
                m[i][j] = v.begin()[i].begin()[j];
            }
        }
    }

    const std::vector<T>& operator [] (const size_t i) const {
        return m[i];
    }

    std::vector<T>& operator [] (const size_t i) {
        return m[i];
    }

    template <typename U>
    Matrix& operator += (const Matrix<U> &rhs) {
        for (size_t i = 0; i != rows; i++) {
            for (int j = 0; j != cols; j++) {
                m[i][j] += rhs[i][j];
            }
        }

        return *this;
    }

    template <typename U>
    Matrix& operator += (const U rhs) {
        for(size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[i][j] += rhs;
            }
        }

        return *this;
    }

    template <typename U>
    Matrix& operator -= (const Matrix<U> &rhs) {
        for (size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[i][j] -= rhs[i][j];
            }
        }

        return *this;
    }

    template <typename U>
    Matrix& operator -= (const U rhs) {
        for(size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[i][j] -= rhs;
            }
        }

        return *this;
    }

    template <typename U>
    Matrix& operator *= (const Matrix<U> &rhs) {
        if (cols != rhs.m.size()) {
            throw std::length_error("first matrices columns should be equal to second matrices rows");
        }

        size_t rhs_cols = rhs.m.begin()->size();
        std::vector<std::vector<T>> r(rows, std::vector<T>(rhs_cols));

        for (size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != rhs_cols; j++) {
                std::vector<T> row(cols, 0);
                std::vector<T> col(cols, 0);

                for (size_t k = 0; k != cols; k++) {
                    row[k] = m[i][k];
                }

                for (size_t k = 0; k != cols; k++) {
                    col[k] = rhs.m[k][j];
                }

                r[i][j] = dot(row, col);
            }
        }

        m = r;
        cols = rhs_cols;
        return *this;
    }

    template <typename U>
    Matrix& operator *= (const U rhs) {
        for(size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[i][j] *= rhs;
            }
        }

        return *this;
    }

    template <typename U>
    Matrix& operator /= (const U rhs) {
        for(size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[i][j] /= rhs;
            }
        }

        return *this;
    }

    const std::vector<T> get_col(const size_t i) const {
        std::vector<T> r(rows);

        for (size_t j = 0; j != rows; j++) {
            r[j] = m[j][i];
        }

        return r;
    }

    std::vector<T> get_row(const size_t i) const {
        std::vector<T> r(cols);

        for (size_t j = 0; j != cols; j++) {
            r[j] = m[i][j];
        }

        return r;
    }

    Matrix& transpose() {
        std::vector<std::vector<T> > r(cols, std::vector<T>(rows, 0));

        for (size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                r[j][i] = m[i][j];
            }
        }

        size_t old_rows = rows;
        rows = cols;
        cols = old_rows;

        m = std::move(r);
        return *this;
    }

    Matrix& invert() {
        // Checks for square matrix
        if (rows != cols) {
            throw std::length_error("rows must be equal to cols for inversion");
        }

        // Creates identity matrix to be converted to inverted matrix
        std::vector<std::vector<T>> r(rows, std::vector<T>(cols, 0));
        for (size_t i = 0; i != rows; i++) {
            r[i][i] = 1;
        }

        std::cout << "created" << std::endl << m << std::endl << r << std::endl << std::endl;

        // Swaps rows in a way that makes each pivot value non-zero
        for (size_t i = 0; i != cols; i++) {
            if (m[i][i] == 0) {
                // Row refers to the row with the biggest value in the current column
                size_t row = i;
                for (size_t j = 0; j != rows; j++) {
                    if (m[j][i] > m[row][i]) {
                        row = j;
                    }
                }

                // If not enough non zero values exist the matrix is singular
                //
                // If row is still equal to i it must be a singular matrix as being within
                // this code block implies the value at this row and column is zero.
                if (row == i) {
                    throw std::logic_error("one or more matrix columns has all 0 values");
                } else {
                    std::swap(m[i], m[row]);
                    std::swap(r[i], r[row]);
                }
            }
        }

        std::cout << "swapped" << std::endl << m << std::endl << r << std::endl << std::endl;
        
        // Sets every value below the diagonal to zero
        for (size_t i = 0; i != cols - 1; i++) {
            for (size_t j = i + 1; j != rows; j++) {
                // Constant to multiply the row element to be added to the current 
                // element by
                const T val = m[j][i] / m[i][i];

                for (size_t k = 0; k != cols; k++) {
                    m[j][k] -= val * m[i][k]; 
                    r[j][k] -= val * r[i][k];
                }

                // Set to zero to account for floating point error
                //m[j][i] = 0;
            }
        }

        std::cout << "low zero" << std::endl << m << std::endl << r << std::endl << std::endl;

        // Set every pivot value to one
        for (size_t i = 0; i != rows; i++) {
            const T val = m[i][i];

            for (size_t j = 0; j != cols; j++) {
                m[i][j] /= val;
                r[i][j] /= val;
            }
        }

        std::cout << "pivots one" << std::endl << m << std::endl << r << std::endl << std::endl;

        // Set every value above the diagonal to zero
        for (size_t i = 0; i != rows; i++) {
            for (size_t j = i + 1; j != cols; j++) {
                const T val = m[i][j];

                for (size_t k = 0; k != cols; k++) {
                    m[i][k] -= val * m[j][k];  
                    r[i][k] -= val * r[j][k];
                }

                m[i][j] = 0;
            }
        }

        std::cout << "high zero" << std::endl << m << std::endl << r << std::endl << std::endl;

        m = std::move(r);
        return *this;
    }

    void clear() {
        for (size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[i][j] = 0;
            }
        }
    }

    void to_identity(size_t size) {
        std::vector<std::vector<T> > r(size, std::vector<T>(size, 0));

        for (size_t i = 0; i != size; i++) {
            r[i][i] = 1;
        }

        rows = size;
        cols = size;

        m = std::move(r);
    }

    void add_row(T value = 0) {
        m.push_back(std::vector<T>(cols, value));

        rows++;
    }

    void add_rows(size_t arows, T value = 0) {
        m.insert(m.end(), arows, std::vector<T>(cols, value));

        rows += arows;
    }

    void remove_row() {
        if (rows == 1) {
            throw std::length_error("matrix rows can not be below 1");
        }

        m.pop_back();

        rows--;
    }

    void remove_rows(size_t arows) {
        if (rows <= arows) {
            throw std::length_error("arows should not be greater then rows");
        }

        m.erase(m.end() - arows, m.end());

        rows -= arows;
    }

    void add_col(T value = 0) {
        for (size_t i = 0; i != rows; i++) {
            m[i].push_back(value);
        }

        cols++;
    }

    void add_cols(size_t acols, T value = 0) {
        for (size_t i = 0; i != rows; i++) {
            m[i].insert(m[i].end(), acols, value);
        }

        cols += acols;
    }

    void remove_col() {
        if (cols == 1) {
            throw std::length_error("matrix cols can not be below 1");
        }

        for (size_t i = 0; i != rows; i++) {
            m[i].pop_back();
        }

        cols--;
    }

    void remove_cols(size_t acols) {
        if (cols <= acols) {
            throw std::length_error("acols should not be greater then cols");
        }

        for (size_t i = 0; i != rows; i++) {
            m[i].erase(m[i].end() - acols, m[i].end());
        }

        cols -= acols;
    }
};

template <typename T, typename U>
Matrix<T> operator + (const Matrix<T> &lhs, Matrix<U> &rhs) {
    Matrix<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator + (const Matrix<T> &lhs, const U rhs) {
    Matrix<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator - (const Matrix<T> &lhs, Matrix<U> &rhs) {
    Matrix<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator - (const Matrix<T> &lhs, const U rhs) {
    Matrix<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator * (const Matrix<T> &lhs, const Matrix<U> &rhs) {
    Matrix<T> r(lhs);

    r *= rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator * (const Matrix<T> &lhs, const U rhs) {
    Matrix<T> r(lhs);

    r *= rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator / (const Matrix<T> &lhs, const U rhs) {
    Matrix<T> r(lhs);

    r /= rhs;

    return r;
}

template <typename T>
std::ostream& operator << (std::ostream &os, const Matrix<T> &m) {
    for (size_t i = 0; i != m.rows; i++) {
        os << "[";

        for (size_t j = 0; j != m.cols; j++) {
            os << m[i][j];
            if (j != m.cols - 1) {
                os << " ";
            }
        }

        os << "]";
        if (i != m.rows - 1) {
            os << "\n";
        }
    }

    return os;
}

template <typename T>
class Vec2 {
public:
    T x, y;

    Vec2(): x(0), y(0) {}

    Vec2(T n): x(n), y(n) {}

    Vec2(T x, T y): x(x), y(y) {}

    template <typename U>
    Vec2(U* v): x(v[0]), y(v[1]) {}

    template <typename U>
    Vec2(std::array<U, 2> &v): x(v[0]), y(v[1]) {}

    template <typename U>
    Vec2(std::initializer_list<U> v): x(v.begin()[0]), y(v.begin()[1]) {}

    template <typename U>
    Vec2(Matrix<U> &v) {
        if (v.rows == 1 && v.cols == 2) {
            x = v[0][0];
            y = v[0][1];
        } else if (v.rows == 2 && v.cols == 1) {
            x = v[0][0];
            y = v[1][0];
        } else {
            throw std::length_error("matrix size should be 1x2 or 2x1");
        }
    }

    template<typename U>
    Vec2(Vec2<U> &v): x(v.x), y(v.y) {}

    T& operator [] (const size_t i) {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
        }

        throw std::range_error("index out of bounds");
    }

    const T& operator [] (const size_t i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        }

        throw std::range_error("index out of bounds");
    }

    template <typename U>
    Vec2<T>& operator += (const Vec2<U>& rhs) {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    template <typename U>
    Vec2<T>& operator += (const U rhs) {
        x += rhs;
        y += rhs;

        return *this;
    }

    template <typename U>
    Vec2<T>& operator -= (const Vec2<U>& rhs) {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }

    template <typename U>
    Vec2<T>& operator -= (const U rhs) {
        x -= rhs;
        y -= rhs;

        return *this;
    }

    Vec2<T>& operator *= (const T rhs) {
        x *= rhs;
        y *= rhs;

        return *this;
    }

    template <typename U>
    Vec2<T>& operator /= (const U rhs) {
        x /= rhs;
        y /= rhs;

        return *this;
    }

    Matrix<T> to_matrix_row() {
        return Matrix<T>({x, y});
    }

    Matrix<T> to_matrix_col() {
        Matrix<T> r(2, 1);

        r[0][0] = x;
        r[1][0] = y;

        return r;
    }

    void clear() {
        x = 0;
        y = 0;
    }
};

template <typename T, typename U>
Vec2<T> operator + (Vec2<T> &lhs, Vec2<U> &rhs) {
    Vec2<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Vec2<T> operator + (Vec2<T> &lhs, const U rhs) {
    Vec2<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Vec2<T> operator - (Vec2<T> &lhs, Vec2<U> &rhs) {
    Vec2<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Vec2<T> operator - (Vec2<T> &lhs, const U rhs) {
    Vec2<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator * (Vec2<T> &lhs, Matrix<U> &rhs) {
    if (rhs.rows != 2) {
        throw std::length_error("rhs.rows should be equal to 2");
    }

    Matrix<T> r(1, rhs.cols);

    std::vector<T> row({lhs.x, lhs.y});
    for (size_t i = 0; i != rhs.cols; i++) {
        std::vector<U> col({rhs[0][i], rhs[1][i]});

        r[0][i] = dot(row, col);
    }

    return r;
}

template <typename T, typename U>
T operator * (Vec2<T> &lhs, Vec2<U> &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T, typename U>
Vec2<T> operator * (Vec2<T> &lhs, const U rhs) {
    Vec2<T> r(lhs);

    r *= rhs;

    return r;
}

template <typename T, typename U>
Vec2<T> operator / (Vec2<T> &lhs, const U rhs) {
    Vec2<T> r(lhs);

    r /= rhs;

    return r;
}

template <typename T>
std::ostream& operator << (std::ostream &os, const Vec2<T> &v) {
    os << "[" << v.x << " " << v.y << "]";

    return os;
}

// Vec3
template <typename T>
class Vec3: public Vec2<T> {
public:
    T z;

    Vec3(): z(0) {}

    Vec3(T n): Vec2<T>(n), z(n) {}

    Vec3(T x, T y, T z): Vec2<T>(x, y), z(z) {}

    template <typename U>
    Vec3(U* v): Vec2<T>(v), z(v[2]) {}

    template <typename U>
    Vec3(std::array<U, 3> &v): Vec2<T>(v[0], v[1]), z(v[2]) {}

    template <typename U>
    Vec3(std::initializer_list<U> v): Vec2<T>(v), z(v.begin()[2]) {}

    template <typename U>
    Vec3(Matrix<U> &v) {
        Vec2<T>::x = v[0][0];
        if (v.rows == 1 && v.cols == 3) {
            Vec2<T>::y = v[0][1];
            z = v[0][2];
        } else if (v.rows == 3 && v.cols == 1) {
            Vec2<T>::y = v[1][0];
            z = v[2][0];
        } else {
            throw std::length_error("matrix size should be 1x3 or 3x1");
        }
    }

    template<typename U>
    Vec3(Vec3<U> &v): Vec2<T>(v.x, v.y), z(v.z) {}

    T& operator [] (const size_t i) {
        switch (i) {
            case 0:
                return Vec2<T>::x;
            case 1:
                return Vec2<T>::y;
            case 2:
                return z;
        }

        throw std::range_error("index out of bounds");
    }

    const T& operator [] (const size_t i) const {
        switch (i) {
            case 0:
                return Vec2<T>::x;
            case 1:
                return Vec2<T>::y;
            case 2:
                return z;
        }

        throw std::range_error("index out of bounds");
    }

    template <typename U>
    Vec3<T>& operator += (const Vec3<U>& rhs) {
        Vec2<T>::x += rhs.x;
        Vec2<T>::y += rhs.y;
        z += rhs.z;

        return *this;
    }

    template <typename U>
    Vec3<T>& operator += (const U rhs) {
        Vec2<T>::operator+=(rhs);
        z += rhs;

        return *this;
    }

    template <typename U>
    Vec3<T>& operator -= (const Vec3<U>& rhs) {
        Vec2<T>::x -= rhs.x;
        Vec2<T>::y -= rhs.y;
        z -= rhs.z;

        return *this;
    }

    template <typename U>
    Vec3<T>& operator -= (const U rhs) {
        Vec2<T>::operator-=(rhs);
        z -= rhs;

        return *this;
    }

    Vec3<T>& operator *= (const T rhs) {
        Vec2<T>::operator*=(rhs);
        z *= rhs;

        return *this;
    }

    template <typename U>
    Vec3<T>& operator /= (const U rhs) {
        Vec2<T>::operator/=(rhs);
        z /= rhs;

        return *this;
    }

    Matrix<T> to_matrix_row() {
        return Matrix<T>({Vec2<T>::x, Vec2<T>::y, z});
    }

    Matrix<T> to_matrix_col() {
        Matrix<T> r(3, 1);

        r[0][0] = Vec2<T>::x;
        r[1][0] = Vec2<T>::y;
        r[2][0] = z;

        return r;
    }

    void clear() {
        Vec2<T>::clear();
        z = 0;
    }
};

template <typename T, typename U>
Vec3<T> operator + (Vec3<T> &lhs, Vec3<U> &rhs) {
    Vec3<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Vec3<T> operator + (Vec3<T> &lhs, const U rhs) {
    Vec3<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Vec3<T> operator - (Vec3<T> &lhs, Vec3<U> &rhs) {
    Vec3<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Vec3<T> operator - (Vec3<T> &lhs, const U rhs) {
    Vec3<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator * (Vec3<T> &lhs, Matrix<U> &rhs) {
    if (rhs.rows != 3) {
        throw std::length_error("rhs.rows should be equal to 3");
    }

    Matrix<T> r(1, rhs.cols);

    std::vector<T> row({lhs.x, lhs.y, lhs.z});
    for (size_t i = 0; i != rhs.cols; i++) {
        std::vector<U> col({rhs[0][i], rhs[1][i], rhs[2][i]});

        r[0][i] = dot(row, col);
    }

    return r;
}

template <typename T, typename U>
T operator * (Vec3<T> &lhs, Vec3<U> &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename T, typename U>
Vec3<T> operator * (Vec3<T> &lhs, const U rhs) {
    Vec3<T> r(lhs);

    r *= rhs;

    return r;
}

template <typename T, typename U>
Vec3<T> operator / (Vec3<T> &lhs, const U rhs) {
    Vec3<T> r(lhs);

    r /= rhs;

    return r;
}

template <typename T> std::ostream& operator << (std::ostream &os, const Vec3<T> &v) {
    os << "[" << v.x << " " << v.y << " " << v.z << "]";

    return os;
}

// Vec4
template <typename T>
class Vec4: public Vec3<T> {
public:
    T w;

    Vec4(): w(0) {}

    Vec4(T n): Vec3<T>(n), w(n) {}

    Vec4(T x, T y, T z, T w): Vec3<T>(x, y, z), w(w) {}

    template <typename U>
    Vec4(U* v): Vec3<T>(v), w(v[3]) {}

    template <typename U>
    Vec4(std::array<U, 4> &v): Vec3<T>(v[0], v[1], v[2]), w(v[3]) {}

    template <typename U>
    Vec4(std::initializer_list<U> v): Vec3<T>(v), w(v.begin()[3]) {}

    template <typename U>
    Vec4(Matrix<U> &v) {
        Vec2<T>::x = v[0][0];
        if (v.rows == 1 && v.cols == 4) {
            Vec2<T>::y = v[0][1];
            Vec3<T>::z = v[0][2];
            w = v[0][3];
        } else if (v.rows == 4 && v.cols == 1) {
            Vec2<T>::y = v[1][0];
            Vec3<T>::z = v[2][0];
            w = v[3][0];
        } else {
            throw std::length_error("matrix size should be 1x4 or 4x1");
        }
    }

    template<typename U>
    Vec4(Vec4<U> &v): Vec3<T>(v.x, v.y, v.z), w(v.w) {}

    T& operator [] (const size_t i) {
        switch (i) {
            case 0:
                return Vec2<T>::x;
            case 1:
                return Vec2<T>::y;
            case 2:
                return Vec3<T>::z;
            case 3:
                return w;
        }

        throw std::range_error("index out of bounds");
    }

    const T& operator [] (const size_t i) const {
        switch (i) {
            case 0:
                return Vec2<T>::x;
            case 1:
                return Vec2<T>::y;
            case 2:
                return Vec3<T>::z;
            case 3:
                return w;
        }

        throw std::range_error("index out of bounds");
    }

    template <typename U>
    Vec4<T>& operator += (const Vec4<U>& rhs) {
        Vec2<T>::x += rhs.x;
        Vec2<T>::y += rhs.y;
        Vec3<T>::z += rhs.z;
        w += rhs.w;

        return *this;
    }

    template <typename U>
    Vec4<T>& operator += (const U rhs) {
        Vec3<T>::operator+=(rhs);
        w += rhs;

        return *this;
    }

    template <typename U>
    Vec4<T>& operator -= (const Vec4<U>& rhs) {
        Vec2<T>::x -= rhs.x;
        Vec2<T>::y -= rhs.y;
        Vec3<T>::z -= rhs.z;
        w -= rhs.w;

        return *this;
    }

    template <typename U>
    Vec4<T>& operator -= (const U rhs) {
        Vec3<T>::operator-=(rhs);
        w -= rhs;

        return *this;
    }

    Vec4<T>& operator *= (const T rhs) {
        Vec3<T>::operator*=(rhs);
        w *= rhs;

        return *this;
    }

    template <typename U>
    Vec4<T>& operator /= (const U rhs) {
        Vec3<T>::operator/=(rhs);
        w /= rhs;

        return *this;
    }

    Matrix<T> to_matrix_row() {
        return Matrix<T>({Vec2<T>::x, Vec2<T>::y, Vec3<T>::z, w});
    }

    Matrix<T> to_matrix_col() {
        Matrix<T> r(4, 1);

        r[0][0] = Vec2<T>::x;
        r[1][0] = Vec2<T>::y;
        r[2][0] = Vec3<T>::z;
        r[3][0] = w;

        return r;
    }

    void clear() {
        Vec3<T>::clear();
        w = 0;
    }
};

template <typename T, typename U>
Vec4<T> operator + (Vec4<T> &lhs, Vec4<U> &rhs) {
    Vec4<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Vec4<T> operator + (Vec4<T> &lhs, const U rhs) {
    Vec4<T> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U>
Vec4<T> operator - (Vec4<T> &lhs, Vec4<U> &rhs) {
    Vec4<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Vec4<T> operator - (Vec4<T> &lhs, const U rhs) {
    Vec4<T> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U>
Matrix<T> operator * (Vec4<T> &lhs, Matrix<U> &rhs) {
    if (rhs.rows != 4) {
        throw std::length_error("rhs.rows should be equal to 4");
    }

    Matrix<T> r(1, rhs.cols);

    std::vector<T> row({lhs.x, lhs.y, lhs.z, lhs.w});
    for (size_t i = 0; i != rhs.cols; i++) {
        std::vector<U> col({rhs[0][i], rhs[1][i], rhs[2][i], rhs[3][i]});

        r[0][i] = dot(row, col);
    }

    return r;
}

template <typename T, typename U>
T operator * (Vec4<T> &lhs, Vec4<U> &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

template <typename T, typename U>
Vec4<T> operator * (Vec4<T> &lhs, const U rhs) {
    Vec4<T> r(lhs);

    r *= rhs;

    return r;
}

template <typename T, typename U>
Vec4<T> operator / (Vec4<T> &lhs, const U rhs) {
    Vec4<T> r(lhs);

    r /= rhs;

    return r;
}

template <typename T> std::ostream& operator << (std::ostream &os, const Vec4<T> &v) {
    os << "[" << v.x << " " << v.y << " " << v.z << " " << v.w << "]";

    return os;
}

template <typename T>
Matrix<T>::Matrix(Vec2<T> &v): m({v.x, v.y}), rows(1), cols(2) {}

template <typename T>
Matrix<T>::Matrix(Vec3<T> &v): m({v.x, v.y, v.z}), rows(1), cols(3) {}

template <typename T>
Matrix<T>::Matrix(Vec4<T> &v): m({v.x, v.y, v.z, v.w}), rows(1), cols(4) {}

#endif
