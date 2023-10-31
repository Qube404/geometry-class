#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <vector>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <iostream>

#include "print.h"

namespace Geometry {

template <typename T, typename U>
T dot(std::vector<T> &lhs, std::vector<U> &rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::length_error("vector lhs and vector rhs should be of same size");
    }

    T r;

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

    void transpose() {
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
    Vec2(Matrix<U> &v): x(v[0][0]), y(v[0][1]) {
        bool valid_size = (v.rows == 1 && v.cols == 2) || (v.rows == 2 && v.cols == 1);
        if (!valid_size) {
            throw std::length_error("matrix size should be 1x2 or 2x1");
        }
    }

    template<typename U>
    Vec2(Vec2<U> &v): x(v.x), y(v.y) {}

    T& operator [] (const unsigned int i) {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
        }

        throw std::range_error("index out of bounds");
    }

    const T& operator [] (const unsigned int i) const {
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
        return Matrix<T>({
            {x},
            {y}
        });
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

    std::array<T, 2> row({lhs.x, lhs.y});
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

/*
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
    Vec3(Matrix<U, 1, 3> &v): Vec2<T>(v[0][0], v[0][1]), z(v[0][2]) {}

    template<typename U>
    Vec3(Matrix<U, 3, 1> &v): Vec2<T>(v[0][0], v[1][0]), z(v[2][0]) {}

    template<typename U>
    Vec3(Vec3<U> &v): Vec2<T>(v.x, v.y), z(v.z) {}

    T& operator [] (const unsigned int i) {
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

    const T& operator [] (const unsigned int i) const {
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
        Vec2<T>::x += rhs;
        Vec2<T>::y += rhs;
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
        Vec2<T>::x -= rhs;
        Vec2<T>::y -= rhs;
        z -= rhs;

        return *this;
    }

    template <typename U>
    Vec3<T>& operator *= (const Vec3<U>& rhs) {
        Vec2<T>::x *= rhs.x;
        Vec2<T>::y *= rhs.y;
        z *= rhs.z;

        return *this;
    }

    template <typename U>
    Vec3<T>& operator *= (const U rhs) {
        Vec2<T>::x *= rhs;
        Vec2<T>::y *= rhs;
        z *= rhs;

        return *this;
    }

    template <typename U>
    Vec3<T>& operator /= (const U rhs) {
        Vec2<T>::x /= rhs;
        Vec2<T>::y /= rhs;
        z /= rhs;

        return *this;
    }

    Matrix<T, 1, 3> to_matrix_row() {
        Matrix<T, 1, 3> r;

        r[0][0] = Vec3<T>::x;
        r[0][1] = Vec3<T>::y;
        r[0][2] = z;

        return r;
    }

    Matrix<T, 3, 1> to_matrix_col() {
        Matrix<T, 3, 1> r;

        r[0][0] = Vec3<T>::x;
        r[1][0] = Vec3<T>::y;
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

template <typename T, typename U, size_t C>
Matrix<T, 1, C> operator * (Vec3<T> &lhs, Matrix<U, 3, C> &rhs) {
    Matrix<T, 1, C> r;

    std::array<T, 3> row = {lhs.x, lhs.y, lhs.z};
    for (size_t i = 0; i != C; i++) {
        std::array<U, 3> col({rhs[0][i], rhs[1][i], rhs[2][i]});

        r[0][i] = dot(row, col);
    }

    return r;
}

template <typename T, typename U>
Vec3<T> operator * (Vec3<T> &lhs, Vec3<U> &rhs) {
    Vec3<T> r(lhs);

    r *= rhs;

    return r;
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

template <typename T>
std::ostream& operator << (std::ostream &os, const Vec3<T> &v) {
    os << "[" << v.x << " " << v.y << " " << v.z << "]";

    return os;
}*/

}
#endif
