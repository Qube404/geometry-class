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

template <typename T, typename U, size_t N>
T dot(std::array<T, N> &lhs, std::array<U, N> &rhs) {
    T r;

    for (size_t i = 0; i != N; i++) {
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
protected:
    std::vector<T> m;

    size_t rows;
    size_t cols;

public:
    Matrix(): m(1, 0), rows(1), cols(1) {}

    Matrix(T n): m(1, n), rows(1), cols(1) {}

    Matrix(size_t rows, size_t cols): m(rows * cols, 0), rows(rows), cols(cols) {}

    Matrix(size_t rows, size_t cols, T n): m(rows * cols, n), rows(rows), cols(cols) {}

    Matrix(T* v, size_t s): m(v, v + s), rows(1), cols(s) {}

    template <size_t S>
    Matrix(std::array<T, S> &v): m(v.begin(), v.end()), rows(1), cols(v.size()) {}

    Matrix(std::initializer_list<T> v): m(v.begin(), v.end()), rows(1), cols(v.size()) {}

    template <size_t C>
    Matrix(T v[][C], size_t rows, size_t cols): m(rows * cols), rows(rows), cols(cols) {
        for (size_t i = 0; i != rows; i++) {
            for (size_t j = 0; j != cols; j++) {
                m[j + i*j] = v[i][j];
            }
        }
    }

    template <size_t R, size_t C>
    Matrix(std::array<std::array<T, C>, R> &v): m(R * C), rows(R), cols(C) {
        for (size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[j + i*j] = v[i][j];
            }
        }
    }

    Matrix(std::initializer_list<std::initializer_list<T>> v): m(v.size() * v.begin()->size()) {
        for (size_t i = 0; i != v.size(); i++) {
            for (size_t j = 0; j != v.begin()->size(); j++) {
                m[j + i*j] = v.begin()[i]->begin()[j];
                
                j++;
            }

            i++;
        }
    }

    const std::vector<T>& operator [] (const size_t i) const {
        return m[i];
    }

    std::vector<T>& operator [] (const size_t i) {
        return m[i];
    }

    template <typename U>
    Matrix<T>& operator += (const Matrix<U> &rhs) {
        for (size_t i = 0; i != rows * cols; i++) {
            rhs
        }

        return *this;
    }

    template <typename U>
    Matrix operator += (const U rhs) {
        for(size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[i][j] += rhs;
            }
        }

        return *this;
    }

    template <typename U>
    Matrix<T, R, C>& operator -= (const Matrix<U, R, C> &rhs) {
        for (size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[i][j] -= rhs[i][j];
            }
        }

        return *this;
    }

    template <typename U>
    Matrix<T, R, C> operator -= (const U rhs) {
        for(size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[i][j] -= rhs;
            }
        }

        return *this;
    }

    template <typename U>
    Matrix<T, R, C> operator *= (const U rhs) {
        for(size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[i][j] *= rhs;
            }
        }

        return *this;
    }

    template <typename U>
    Matrix<T, R, C> operator /= (const U rhs) {
        for(size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[i][j] /= rhs;
            }
        }

        return *this;
    }

    std::array<T, R> get_col(const size_t i) const {
        std::array<T, R> r;

        for (size_t j = 0; j != R; j++) {
            r[j] = m[j][i];
        }

        return r;
    }

    std::array<T, C> get_row(const size_t i) const {
        std::array<T, C> r;

        for (size_t j = 0; j != C; j++) {
            r[j] = m[i][j];
        }

        return r;
    }

    Matrix<T, C, R> transpose() const {
        Matrix<T, C, R> r;

        for (size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                r[i][j] = m[j][i];
            }
        }

        return r;
    }

    void clear() {
        for (size_t i = 0; i != R; i++) {
            for (size_t j = 0; j != C; j++) {
                m[i][j] = 0;            
            }
        }
    }

};

template <typename T, typename U, size_t R, size_t C>
Matrix<T, R, C> operator + (const Matrix<T, R, C> &lhs, Matrix<U, R, C> &rhs) {
    Matrix<T, R, C> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U, size_t R, size_t C>
Matrix<T, R, C> operator + (const Matrix<T, R, C> &lhs, const U rhs) {
    Matrix<T, R, C> r(lhs);

    r += rhs;

    return r;
}

template <typename T, typename U, size_t R, size_t C>
Matrix<T, R, C> operator - (const Matrix<T, R, C> &lhs, Matrix<U, R, C> &rhs) {
    Matrix<T, R, C> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U, size_t R, size_t C>
Matrix<T, R, C> operator - (const Matrix<T, R, C> &lhs, const U rhs) {
    Matrix<T, R, C> r(lhs);

    r -= rhs;

    return r;
}

template <typename T, typename U, size_t R, size_t C, size_t K>
Matrix<T, R, K> operator * (const Matrix<T, R, C> &lhs, const Matrix<U, C, K> &rhs) {
    Matrix<T, R, K> r;

   for (size_t i = 0; i != R; i++) {
        for (size_t j = 0; j != K; j++) {
            std::array<T, C> row;
            std::array<T, C> col;

            for (size_t k = 0; k != C; k++) {
                row[k] = lhs[i][k];
            }

            for (size_t k = 0; k != C; k++) {
                col[k] = rhs[k][j];
            }

            r[i][j] = dot(row, col);
        }
    }

    return r;
}

template <typename T, typename U, size_t R, size_t C>
Matrix<T, R, C> operator * (const Matrix<T, R, C> &lhs, const U rhs) {
    Matrix<T, R, C> r(lhs);

    r *= rhs;

    return r;
}

template <typename T, typename U, size_t R, size_t C>
Matrix<T, R, C> operator / (const Matrix<T, R, C> &lhs, const U rhs) {
    Matrix<T, R, C> r(lhs);

    r /= rhs;

    return r;
}

template <typename T, size_t N>
void to_identity_matrix(Matrix<T, N, N> &m) {
    m.clear();

    for (size_t i = 0; i != N; i++) {
        m[i][i] = 1;
    }
}

template <typename T, size_t N>
Matrix<T, N, N> create_identity_matrix() {
    Matrix<T, N, N> r;

    for (size_t i = 0; i != N; i++) {
        r[i][i] = 1;
    }

    return r;
}

template <typename T, size_t R, size_t C>
std::ostream& operator << (std::ostream &os, const Matrix<T, R, C> &m) {
    for (size_t i = 0; i != R; i++) {
        os << "[";

        for (size_t j = 0; j != C; j++) {
            os << m[i][j];
            if (j != C - 1) {
                os << " ";
            }
        }

        os << "]";
        if (i != R - 1) {
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
    Vec2(Matrix<U, 1, 2> &v): x(v[0][0]), y(v[0][1]) {}

    template<typename U>
    Vec2(Matrix<U, 2, 1> &v): x(v[0][0]), y(v[1][0]) {}

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

    template <typename U>
    Vec2<T>& operator *= (const Vec2<U>& rhs) {
        x *= rhs.x;
        y *= rhs.y;

        return *this;
    }

    template <typename U>
    Vec2<T>& operator *= (const U rhs) {
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

    Matrix<T, 1, 2> to_matrix_row() {
        Matrix<T, 1, 2> r;

        r[0][0] = x;
        r[0][1] = y;

        return r;
    }

    Matrix<T, 2, 1> to_matrix_col() {
        Matrix<T, 2, 1> r;

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

template <typename T, typename U, size_t C>
Matrix<T, 1, C> operator * (Vec2<T> &lhs, Matrix<U, 2, C> &rhs) {
    Matrix<T, 1, C> r;

    std::array<T, 2> row = {lhs.x, lhs.y};
    for (size_t i = 0; i != C; i++) {
        std::array<U, 2> col({rhs[0][i], rhs[1][i]});

        r[0][i] = dot(row, col);
    }

    return r;
}

template <typename T, typename U>
Vec2<T> operator * (Vec2<T> &lhs, Vec2<U> &rhs) {
    Vec2<T> r(lhs);

    r *= rhs;

    return r;
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
}

}
#endif
