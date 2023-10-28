#include <iostream>
#include <initializer_list>
#include <vector>

#include "geometry.h"
#include "print.h"

using namespace Geometry;

void test_matrix() {
    Geometry::Matrix<float, 1, 3> a;
    Geometry::Matrix<float, 1, 3> b(4);
    
    float carr[3] = {1, 2, 3};
    Geometry::Matrix<float, 1, 3> c(carr, 3);
    Geometry::Matrix<float, 1, 3> d({1, 2, 3});

    float earr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Geometry::Matrix<float, 3, 3> e(earr, 3, 3);
    Geometry::Matrix<float, 3, 3> f({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    e.clear();
    float g = f[0][0];
    int h = f[0][0];

    const Geometry::Matrix<float, 3, 3> l({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    const float m = f[1][0];

    f += l;
    f += 2;
    f -= l;
    f -= 2;
    f *= 10;
    f /= 2;

    std::array<float, 3> o = l.get_col(0);
    std::array<float, 3> p = l.get_row(2);

    Geometry::Matrix<float, 3, 3> n = l.transpose();

    l + l;
    l + 2;

    l - l;
    l - 2;

    const Geometry::Matrix<float, 2, 3> q({
        {1, 2, 3},
        {4, 5, 6}
    });

    const Geometry::Matrix<float, 3, 2> r({
        {7, 8},
        {9, 10},
        {11, 12}
    });

    q * r;
    l * 2;

    l / 2;
}

void test_vec2() {
    Vec2<float> a;
    Vec2<float> b(4);
    Vec2<float> c(5, 6);

    float d[2] = {7, 8};
    Vec2<float> e(d);
    Vec2<int> f(d);

    std::array<float, 2> g = {9, 1};
    Vec2<float> h(g);
    Vec2<float> l({2, 3});

    Matrix<float, 1, 2> m({1.1, 2.1});
    Vec2<float> n(m);
    Vec2<int> o(m);

    Matrix<float, 2, 1> p(3);
    Vec2<float> q(p);
    Vec2<float> r(q);

    float s = r[0];
    const float t = r[1];

    b += c; 
    b += 2;

    e -= c; 
    e -= 2;

    h *= l;
    h *= 2;

    n /= 2;

    b.to_matrix_row();
    b.to_matrix_col();

    e.x = 4;
    e.y = 7;
    e.clear();

    b + c; 
    b + 2;

    e - c; 
    e - 2;

    h * l;
    h * 2;

    Matrix<float, 2, 5> x({
        {7, 3, 4, 8, 9},
        {4, 9, 1, 8, 5}
    });
    Vec2<int> u(3, 7);
    u * x;

    n / 2;
}

void test_vec3() {
    Vec3<float> a;
    Vec3<float> b(4);
    Vec3<float> c(5, 6, 7);

    float d[3] = {7, 8, 9};
    Vec3<float> e(d);
    Vec3<int> f(d);

    std::array<float, 3> g = {9, 1, 2};
    Vec3<float> h(g);
    Vec3<float> l({2, 3, 4});

    Matrix<float, 1, 3> m({1, 2, 3});
    Vec3<float> n(m);
    Vec3<int> o(m);

    Matrix<float, 3, 1> p(3);
    Vec3<float> q(p);
    Vec3<float> r(q);

    float s = r[0];
    const int t = r[1];
    const float z = r[2];

    b += c; 
    b += 2;

    e -= c; 
    e -= 2;

    h *= l;
    h *= 2;

    n /= 2;

    b.to_matrix_row();
    b.to_matrix_col();

    b.clear();

    b + c;
    b + 2;

    e - c; 
    e - 2;

    h * l;
    h * 2;

    Matrix<float, 3, 3> x({
        {4, 3, 4},
        {4, 2, 1},
        {3, 3, 2}
    });
    Vec3<int> u(3, 2, 2);
    u * x;

    n / 2;
}

void test_vec4() {
    Vec3<float> a;
    std::cout << a << std::endl;
    Vec3<float> b(4);
    std::cout << b << std::endl;
    Vec3<float> c(5, 6, 7);
    std::cout << c << std::endl;

    float d[3] = {7, 8, 9};
    Vec3<float> e(d);
    std::cout << e << std::endl;
    Vec3<int> f(d);
    std::cout << f << std::endl;

    std::array<float, 3> g = {9, 1, 2};
    Vec3<float> h(g);
    std::cout << h << std::endl;
    Vec3<float> l({2, 3, 4});
    std::cout << l << std::endl;

    Matrix<float, 1, 3> m({1, 2, 3});
    Vec3<float> n(m);
    std::cout << n << std::endl;
    Vec3<int> o(m);
    std::cout << o << std::endl;

    Matrix<float, 3, 1> p(3);
    Vec3<float> q(p);
    std::cout << q << std::endl;
    Vec3<float> r(q);
    std::cout << r << std::endl;

    float s = r[0];
    std::cout << s << std::endl;
    const int t = r[1];
    std::cout << t << std::endl;
    const float z = r[2];
    std::cout << z << std::endl;

    std::cout << b << " " << c << std::endl;
    b += c; 
    std::cout << b << std::endl;
    b += 2;
    std::cout << b << std::endl;

    std::cout << e << " " << c << std::endl;
    e -= c; 
    std::cout << e << std::endl;
    e -= 2;
    std::cout << e << std::endl;

    std::cout << h << " " << l << std::endl;
    h *= l;
    std::cout << h << std::endl;
    h *= 2;
    std::cout << h << std::endl;

    std::cout << n << std::endl;
    n /= 2;
    std::cout << n << std::endl;

    std::cout << b.to_matrix_row() << std::endl;
    std::cout << b.to_matrix_col() << std::endl;

    std::cout << b << std::endl;
    b.clear();
    std::cout << b << std::endl;

    std::cout << b + c << std::endl;
    std::cout << b + 2 << std::endl;

    std::cout << e - c << std::endl; 
    std::cout << e - 2 << std::endl;

    std::cout << h * l << std::endl;
    std::cout << h * 2 << std::endl;

    std::cout << n / 2 << std::endl;
}

int main() {
    test_matrix();
    test_vec2();
    test_vec3();
}
