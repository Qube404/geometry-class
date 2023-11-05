#include <iostream>
#include <initializer_list>
#include <vector>

#include "geometry.h"
#include "print.h"

void test_matrix() {
    using namespace std;

    Matrix<float> a;
    cout << "a: " << endl << a << endl << endl;

    Matrix<float> b(3);
    cout << "b: " << endl << b << endl << endl;

    Matrix<float> ab(1, 3);
    cout << "ab: " << endl << ab << endl << endl;

    Matrix<float> ba(2, 3, 4);
    cout << "ba: " << endl << ba << endl << endl;

    float carr[3] = {1, 2, 3};
    Matrix<float> c(carr, 3);
    cout << "c: " << endl << c << endl << endl;

    std::array<float, 3> ac({1, 2, 3});
    Matrix<float> ca(ac);
    cout << "ca: " << endl << ca << endl << endl; 

    Matrix<float> d({1, 2, 3});
    cout << "d: " << endl << d << endl << endl;

    float earr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Matrix<float> e(earr, 3, 3);
    cout << "e: " << endl << e << endl << endl;

    std::array<std::array<float, 3>, 2> ef({
        std::array<float, 3>({1, 2, 3}),
        std::array<float, 3>({6, 5, 4})
    });
    Matrix<float> fe(ef);
    cout << "fe: " << endl << fe << endl << endl; 

    Matrix<float> f({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    cout << "f: " << endl << f << endl << endl;

    float g = f[0][0];
    cout << "g, f[0][0]: " << g << endl << endl;
    int h = f[2][2];
    cout << "h, f[2][2]: " << h << endl << endl;

    const Matrix<float> l({
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

    const Matrix<float> q({
        {1, 2, 3},
        {4, 5, 6}
    });

    const Matrix<float> r({
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
    using namespace std;

    Vec2<float> a;
    cout << "a: " << a << endl << endl;

    Vec2<float> b(4);
    cout << "b: " << b << endl << endl;

    Vec2<float> c(5, 6);
    cout << "c: " << c << endl << endl;

    float d[2] = {7, 8};
    Vec2<float> e(d);
    cout << "e: " << e << endl << endl;

    Vec2<int> f(d);
    cout << "f: " << f << endl << endl;

    std::array<float, 2> g = {9, 1};
    cout << "g: " << g << endl << endl;

    Vec2<float> h(g);
    cout << "h: " << h << endl << endl;

    Vec2<float> l({2, 3});
    cout << "l: " << l << endl << endl;

    Matrix<float> m({1.1, 2.1});
    cout << "m: " << m << endl << endl;

    Vec2<float> n(m);
    cout << "n: " << n << endl << endl;

    Vec2<int> o(m);
    cout << "o: " << o << endl << endl;

    Vec2<float> q(4);
    cout << "q: " << q << endl << endl;

    Vec2<float> r(q);
    cout << "r: " << r << endl << endl;

    float s = r[0];
    cout << "s, r[0]: " << s << endl << endl;

    const float t = r[1];
    cout << "t, r[1]: " << t << endl << endl;

    cout << "b: " << b << endl << "c: " << c << endl << endl;
    b += c;
    cout << "b += c: " << b << endl << endl;

    b += 2;
    cout << "b += 2: " << b << endl << endl;

    cout << "e: " << e << endl << "c: " << c << endl << endl;
    e -= c; 
    cout << "e -= c: " << e << endl << endl;

    e -= 2;
    cout << "e -= 2: " << e << endl << endl;

    cout << "h: " << h << endl << endl;
    h *= 2;
    cout << "h *= 2: " << h << endl << endl;

    cout << "n: " << n << endl << endl;
    n /= 2;
    cout << "n /= 2: " << n << endl << endl;

    cout << "b.to_matrix_row(): " << b.to_matrix_row() << endl;
    cout << "b.to_matrix_col(): " << endl << b.to_matrix_col() << endl << endl;

    e.x = 4;
    e.y = 7;
    cout << "e: " << e << endl << endl;
    e.clear();
    cout << "e.clear(): " << e << endl << endl;

    cout << "b: " << b << endl << "c: " << c << endl << endl;
    cout << "b + c: " << b + c << endl << endl; 
    cout << "b + 2: " << b + 2 << endl << endl;

    cout << "e: " << e << endl << "c: " << c << endl << endl;
    cout << "e - c: " << e - c << endl << endl; 
    cout << "e - 2: " << e - 2 << endl << endl;

    cout << "h: " << h << endl << "l: " << l << endl << endl;
    cout << "h * l: " << h * l << endl << endl;
    cout << "h * 2: " << h * 2 << endl << endl;

    Matrix<float> x({
        {7, 3, 4, 8, 9},
        {4, 9, 1, 8, 5}
    });
    Vec2<int> u(3, 7);
    cout << "x: " << endl << x << endl << endl << "u: " << u << endl << endl;
    cout << "u * x: " << u * x << endl << endl;

    cout << "n: " << endl << n << endl;
    cout << "n / 2: " << n / 2 << endl << endl;
}

void test_vec3() {
    using namespace std;

    Vec3<float> a;
    cout << "a: " << a << endl << endl;

    Vec3<float> b(4);
    cout << "b: " << b << endl << endl;

    Vec3<float> c(5, 6, 7);
    cout << "c: " << c << endl << endl;

    float d[3] = {7, 8, 9};
    Vec3<float> e(d);
    cout << "e: " << e << endl << endl;

    Vec3<int> f(d);
    cout << "f: " << f << endl << endl;

    std::array<float, 3> g = {9, 1, 2};
    cout << "g: " << g << endl << endl;

    Vec3<float> h(g);
    cout << "h: " << h << endl << endl;

    Vec3<float> l({2, 3, 4});
    cout << "l: " << l << endl << endl;

    Matrix<float> m({1.1, 2.1, 3.2});
    cout << "m: " << m << endl << endl;

    Vec3<float> n(m);
    cout << "n: " << n << endl << endl;

    Vec3<int> o(m);
    cout << "o: " << o << endl << endl;

    Vec3<float> q(4);
    cout << "q: " << q << endl << endl;

    Vec3<float> r(q);
    cout << "r: " << r << endl << endl;

    float s = r[0];
    cout << "s, r[0]: " << s << endl << endl;

    const float t = r[1];
    cout << "t, r[1]: " << t << endl << endl;

    s = r[2];
    cout << "t, r[2]: " << t << endl << endl;

    cout << "b: " << b << endl << "c: " << c << endl << endl;
    b += c;
    cout << "b += c: " << b << endl << endl;

    b += 2;
    cout << "b += 2: " << b << endl << endl;

    cout << "e: " << e << endl << "c: " << c << endl << endl;
    e -= c; 
    cout << "e -= c: " << e << endl << endl;

    e -= 2;
    cout << "e -= 2: " << e << endl << endl;

    cout << "h: " << h << endl << endl;
    h *= 2;
    cout << "h *= 2: " << h << endl << endl;

    cout << "n: " << n << endl << endl;
    n /= 2;
    cout << "n /= 2: " << n << endl << endl;

    cout << "b.to_matrix_row(): " << b.to_matrix_row() << endl;
    cout << "b.to_matrix_col(): " << endl << b.to_matrix_col() << endl << endl;

    e.x = 4;
    e.y = 7;
    e.z = 4;
    cout << "e: " << e << endl << endl;
    e.clear();
    cout << "e.clear(): " << e << endl << endl;

    cout << "b: " << b << endl << "c: " << c << endl << endl;
    cout << "b + c: " << b + c << endl << endl; 
    cout << "b + 2: " << b + 2 << endl << endl;

    cout << "e: " << e << endl << "c: " << c << endl << endl;
    cout << "e - c: " << e - c << endl << endl; 
    cout << "e - 2: " << e - 2 << endl << endl;

    cout << "h: " << h << endl << "l: " << l << endl << endl;
    cout << "h * l: " << h * l << endl << endl;
    cout << "h * 2: " << h * 2 << endl << endl;

    Matrix<float> x({
        {7, 3, 4, 8, 9},
        {4, 9, 1, 8, 5},
        {2, 3, 1, 6, 9}
    });
    Vec3<int> u(3, 7, 8);
    cout << "x: " << endl << x << endl << endl << "u: " << u << endl << endl;
    cout << "u * x: " << u * x << endl << endl;

    cout << "n: " << endl << n << endl;
    cout << "n / 2: " << n / 2 << endl << endl;
}

void test_vec4() {
    using namespace std;

    Vec4<float> a;
    cout << "a: " << a << endl << endl;

    Vec4<float> b(4);
    cout << "b: " << b << endl << endl;

    Vec4<float> c(5, 6, 7, 8);
    cout << "c: " << c << endl << endl;

    float d[4] = {7, 8, 9, 1};
    Vec4<float> e(d);
    cout << "e: " << e << endl << endl;

    Vec4<int> f(d);
    cout << "f: " << f << endl << endl;

    std::array<float, 4> g = {9, 1, 2, 3};
    cout << "g: " << g << endl << endl;

    Vec4<float> h(g);
    cout << "h: " << h << endl << endl;

    Vec4<float> l({2, 3, 4, 5});
    cout << "l: " << l << endl << endl;

    Matrix<float> m({1.1, 2.1, 3.2, 4.4});
    cout << "m: " << m << endl << endl;

    Vec4<float> n(m);
    cout << "n: " << n << endl << endl;

    Vec4<int> o(m);
    cout << "o: " << o << endl << endl;

    Vec4<float> q(4);
    cout << "q: " << q << endl << endl;

    Vec4<float> r(q);
    cout << "r: " << r << endl << endl;

    float s = r[0];
    cout << "s, r[0]: " << s << endl << endl;

    const float t = r[1];
    cout << "t, r[1]: " << t << endl << endl;

    s = r[2];
    cout << "t, r[2]: " << t << endl << endl;

    s = r[3];
    cout << "t, r[3]: " << t << endl << endl;

    cout << "b: " << b << endl << "c: " << c << endl << endl;
    b += c;
    cout << "b += c: " << b << endl << endl;

    b += 2;
    cout << "b += 2: " << b << endl << endl;

    cout << "e: " << e << endl << "c: " << c << endl << endl;
    e -= c; 
    cout << "e -= c: " << e << endl << endl;

    e -= 2;
    cout << "e -= 2: " << e << endl << endl;

    cout << "h: " << h << endl << endl;
    h *= 2;
    cout << "h *= 2: " << h << endl << endl;

    cout << "n: " << n << endl << endl;
    n /= 2;
    cout << "n /= 2: " << n << endl << endl;

    cout << "b.to_matrix_row(): " << b.to_matrix_row() << endl;
    cout << "b.to_matrix_col(): " << endl << b.to_matrix_col() << endl << endl;

    e.x = 4;
    e.y = 7;
    e.z = 8;
    e.w = 2;
    cout << "e: " << e << endl << endl;
    e.clear();
    cout << "e.clear(): " << e << endl << endl;

    cout << "b: " << b << endl << "c: " << c << endl << endl;
    cout << "b + c: " << b + c << endl << endl; 
    cout << "b + 2: " << b + 2 << endl << endl;

    cout << "e: " << e << endl << "c: " << c << endl << endl;
    cout << "e - c: " << e - c << endl << endl; 
    cout << "e - 2: " << e - 2 << endl << endl;

    cout << "h: " << h << endl << "l: " << l << endl << endl;
    cout << "h * l: " << h * l << endl << endl;
    cout << "h * 2: " << h * 2 << endl << endl;

    Matrix<float> x({
        {7, 3},
        {4, 9},
        {2, 3},
        {8, 5}
    });
    Vec4<int> u(3, 7, 8, 5);
    cout << "x: " << endl << x << endl << endl << "u: " << u << endl << endl;
    cout << "u * x: " << u * x << endl << endl;

    cout << "n: " << endl << n << endl;
    cout << "n / 2: " << n / 2 << endl << endl;
}

int main() {
    using namespace std;

    Matrix<float> m({
        {3, 2},
        {-2, -1},
    });
    Matrix<float> n(m);
    m.invert();

    n * m;
}
