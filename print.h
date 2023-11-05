#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <array>
#include <vector>

template <typename T, size_t N>
std::ostream& operator << (std::ostream &os, const std::array<T, N> &m) {
    for (int i = 0; i != N; i++) {
        os << m[i];
        if (i != N) {
            os << " ";
        }
    }

    return os;
}

template <typename T>
std::ostream& operator << (std::ostream &os, const std::vector<T> &m) {
    for (int i = 0; i != m.size(); i++) {
        os << m[i];
        if (i != m.size()) {
            os << " ";
        }
    }

    return os;
}

template <typename T>
std::ostream& operator << (std::ostream &os, const std::vector<std::vector<T>> &m) {
    for (int i = 0; i != m.size(); i++) {
        for (int j = 0; j != m[i].size(); j++) {
            os << m[i][j] << " ";
        }
        os << std::endl;
    }

    return os;
}

template <typename T>
void println(T o) {
    std::cout << o << std::endl;
}

#endif
