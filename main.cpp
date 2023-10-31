#include <iostream>
#include <initializer_list>
#include <vector>

#include "geometry.h"
#include "print.h"

using namespace Geometry;

void test_matrix() {
    using namespace std;

    Geometry::Matrix<float> a;
    cout << "a: " << endl << a << endl << endl;

    Geometry::Matrix<float> b(3);
    cout << "b: " << endl << b << endl << endl;

    Geometry::Matrix<float> ab(1, 3);
    cout << "ab: " << endl << ab << endl << endl;

    Geometry::Matrix<float> ba(2, 3, 4);
    cout << "ba: " << endl << ba << endl << endl;

    
    float carr[3] = {1, 2, 3};
    Geometry::Matrix<float> c(carr, 3);
    cout << "c: " << endl << c << endl << endl;

    std::array<float, 3> ac({1, 2, 3});
    Geometry::Matrix<float> ca(ac);
    cout << "ca: " << endl << ca << endl << endl; 

    Geometry::Matrix<float> d({1, 2, 3});
    cout << "d: " << endl << d << endl << endl;

    float earr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Geometry::Matrix<float> e(earr, 3, 3);
    cout << "e: " << endl << e << endl << endl;

    std::array<std::array<float, 3>, 2> ef({
        std::array<float, 3>({1, 2, 3}),
        std::array<float, 3>({6, 5, 4})
    });
    Geometry::Matrix<float> fe(ef);
    cout << "fe: " << endl << fe << endl << endl; 

    Geometry::Matrix<float> f({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    cout << "f: " << endl << f << endl << endl;

    float g = f[0][0];
    cout << "g, f[0][0]: " << g << endl << endl;
    int h = f[2][2];
    cout << "h, f[2][2]: " << h << endl << endl;

    const Geometry::Matrix<float> l({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    cout << "l: " << endl << l << endl << endl;

    const float m = f[1][0];
    cout << "m, f[1][0]: " << m << endl << endl;

    cout << "f: " << endl << f << endl << endl << "l: " << endl << l << endl << endl;
    f += l;
    cout << "f += l: " << endl << f << endl << endl;

    f += 2;
    cout << "f += 2: " << endl << f << endl << endl;

    f -= l;
    cout << "f -= l: " << endl << f << endl << endl;

    f -= 2;
    cout << "f -= 2: " << endl << f << endl << endl;

    f *= l;
    cout << "f *= l: " << endl << f << endl << endl;

    f *= 10;
    cout << "f *= 10: " << endl << f << endl << endl;

    f /= 2;
    cout << "f /= 2: " << endl << f << endl << endl;

    cout << "l: " << endl << l << endl << endl;
    std::vector<float> o = l.get_col(0);
    cout << "o, l.get_col(0): " << o << endl;
    std::vector<float> p = l.get_row(2);
    cout << "p, l.get_row(2): " << p << endl << endl;

    cout << "f: " << endl << f << endl << endl;
    f.transpose();
    cout << "f.transpose(): " << endl << f << endl << endl;

    e.clear();
    cout << "e.clear(): " << endl << e << endl << endl;

    e.to_identity(3);
    cout << "e.to_identity(3): " << endl << e << endl << endl;

    e.to_identity(10);
    cout << "e.to_identity(10): " << endl << e << endl << endl;

    e.add_row();
    cout << "e.add_row(): " << endl << e << endl << endl;

    e.add_row(2);
    cout << "e.add_row(2): " << endl << e << endl << endl;

    e.add_rows(2, 4);
    cout << "e.add_rows(2, 4): " << endl << e << endl << endl;

    e.remove_row();
    cout << "e.remove_row(): " << endl << e << endl << endl;

    e.remove_rows(2);
    cout << "e.remove_rows(2): " << endl << e << endl << endl;

    e.add_col();
    cout << "e.add_col(): " << endl << e << endl << endl;

    e.add_col(2);
    cout << "e.add_col(2): " << endl << e << endl << endl;

    e.add_cols(2, 4);
    cout << "e.add_cols(2, 4): " << endl << e << endl << endl;

    e.remove_col();
    cout << "e.remove_col(): " << endl << e << endl << endl;

    e.remove_cols(2);
    cout << "e.remove_cols(2): " << endl << e << endl << endl;

    cout << "l: " << endl << l << endl;
    cout << "l + l: " << endl << l + l << endl << endl;
    cout << "l + 2: " << endl << l + 2 << endl << endl;

    cout << "l - l: " << endl << l - l << endl << endl;
    cout << "l - 2: " << endl << l - 2 << endl << endl;

    const Geometry::Matrix<float> q({
        {1, 2, 3},
        {4, 5, 6}
    });

    const Geometry::Matrix<float> r({
        {7, 8},
        {9, 10},
        {11, 12}
    });

    cout << "q: " << endl << q << endl << endl;
    cout << "r: " << endl << r << endl << endl;
    cout << "q * r: " << endl << q * r << endl << endl;
    cout << "l * 2: " << endl << l * 2 << endl << endl;

    cout << "l / 2: " << endl << l / 2 << endl << endl;
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

    Matrix<float> m({1.1, 2.1});
    Vec2<float> n(m);
    Vec2<int> o(m);

    Vec2<float> q(4);
    Vec2<float> r(q);

    float s = r[0];
    const float t = r[1];

    b += c; 
    b += 2;

    e -= c; 
    e -= 2;

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

    Matrix<float> x({
        {7, 3, 4, 8, 9},
        {4, 9, 1, 8, 5}
    });
    Vec2<int> u(3, 7);
    u * x;

    n / 2;
}

/*
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
*/

int main() {
    test_matrix();
}
