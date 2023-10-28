#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <array>

template <typename T, size_t N>
std::ostream& operator << (std::ostream &os, std::array<T, N> &m) {
    for (int i = 0; i != N; i++) {
        os << m[i];
        if (i != N) {
            os << " ";
        }
    }

    return os;
}

template <typename T>
void prt_wnl(T o) {
    std::cout << o << std::endl;
}

#endif
