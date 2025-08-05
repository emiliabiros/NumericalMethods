#include <iostream>
#include "function.h"
using namespace std;

class FAD {
private:
    double f;
    double fx;
    double fy;
    double fxx;
    double fxy;
    double fyy;

public:
    FAD() : f(0.0), fx(0.0), fy(0.0), fxx(0.0), fxy(0.0), fyy(0.0) {}

    explicit FAD(double value) : f(value), fx(0.0), fy(0.0), fxx(0.0), fxy(0.0), fyy(0.0) {}

    FAD(double value, bool isX) : f(value), fx(isX ? 1.0 : 0.0), fy(isX ? 0.0 : 1.0), fxx(0.0), fxy(0.0), fyy(0.0) {}

    explicit FAD(int value) { fx = fy = fxx = fxy = fyy = 0.; f = static_cast<double>(value); }

    FAD(const FAD& other) {
        f = other.f;
        fx = other.fx;
        fy = other.fy;
        fxx = other.fxx;
        fxy = other.fxy;
        fyy = other.fyy;
    }

    double getF() const { return f; }
    double getFx() const { return fx; }
    double getFy() const { return fy; }
    double getFxx() const { return fxx; }
    double getFxy() const { return fxy; }
    double getFyy() const { return fyy; }

    FAD& operator=(const FAD& other) {
        if (this != &other) {
            f = other.f;
            fx = other.fx;
            fy = other.fy;
            fxx = other.fxx;
            fxy = other.fxy;
            fyy = other.fyy;
        }
        return *this;
    }

    FAD operator+(const FAD& rhs) const {
        FAD result(0);
        result.f = f + rhs.f;
        result.fx = fx + rhs.fx;
        result.fy = fy + rhs.fy;
        result.fxx = fxx + rhs.fxx;
        result.fxy = fxy + rhs.fxy;
        result.fyy = fyy + rhs.fyy;
        return result;
    }

    FAD operator-(const FAD& rhs) const {
        FAD result(0);
        result.f = f - rhs.f;
        result.fx = fx - rhs.fx;
        result.fy = fy - rhs.fy;
        result.fxx = fxx - rhs.fxx;
        result.fxy = fxy - rhs.fxy;
        result.fyy = fyy - rhs.fyy;
        return result;
    }

    FAD operator*(const FAD& rhs) const {
        FAD result;
        result.f = f * rhs.f;
        result.fx = fx * rhs.f + f * rhs.fx;
        result.fy = fy * rhs.f + f * rhs.fy;
        result.fxx = fxx * rhs.f + 2.0 * fx * rhs.fx + f * rhs.fxx;
        result.fxy = fxy * rhs.f + fx * rhs.fy + fy * rhs.fx + f * rhs.fxy;
        result.fyy = fyy * rhs.f + 2.0 * fy * rhs.fy + f * rhs.fyy;
        return result;
    }

    FAD operator/(const FAD& rhs) const {
        FAD result;
        result.f = f / rhs.f;
        result.fx = (fx * rhs.f - f * rhs.fx) / (rhs.f * rhs.f);
        result.fy = (fy * rhs.f - f * rhs.fy) / (rhs.f * rhs.f);
        result.fxx = (fxx * rhs.f - f * rhs.fxx) / (rhs.f * rhs.f) - 2.0 * rhs.fx * (fx * rhs.f - f * rhs.fx) / (rhs.f * rhs.f * rhs.f);
        result.fxy = (fxy * rhs.f - f * rhs.fxy) / (rhs.f * rhs.f) - (rhs.fy * (fx * rhs.f - f * rhs.fx) + rhs.fx * (fy * rhs.f - f * rhs.fy)) / (rhs.f * rhs.f * rhs.f);
        result.fyy = (fyy * rhs.f - f * rhs.fyy) / (rhs.f * rhs.f) - 2.0 * rhs.fy * (fy * rhs.f - f * rhs.fy) / (rhs.f * rhs.f * rhs.f);
        return result;
    }

    FAD operator-() const {
        FAD result(0);
        result.f = -f;
        result.fx = -fx;
        result.fy = -fy;
        result.fxx = -fxx;
        result.fxy = -fxy;
        result.fyy = -fyy;
        return result;
    }

    friend FAD operator+(double lhs, const FAD& rhs) {
        return FAD(lhs) + rhs;
    }

    friend FAD operator-(double lhs, const FAD& rhs) {
        return FAD(lhs) - rhs;
    }

    friend FAD operator*(double lhs, const FAD& rhs) {
        return FAD(lhs) * rhs;
    }

    friend FAD operator/(double lhs, const FAD& rhs) {
        return FAD(lhs) / rhs;
    }

    FAD operator+(double rhs) const {
        return *this + FAD(rhs);
    }
    FAD operator-(double rhs) const {
        return *this - FAD(rhs);
    }
    FAD operator*(double rhs) const {
        return *this * FAD(rhs);
    }
    FAD operator/(double rhs) const {
        return *this / FAD(rhs);
    }

    friend FAD sin(const FAD& v) {
        FAD result;
        double s = sin(v.f);
        double c = cos(v.f);
        result.f = s;
        result.fx = c * v.fx;
        result.fy = c * v.fy;
        result.fxx = -s * v.fx * v.fx + c * v.fxx;
        result.fxy = -s * v.fx * v.fy + c * v.fxy;
        result.fyy = -s * v.fy * v.fy + c * v.fyy;
        return result;
    }

    friend FAD cos(const FAD& x) {
        FAD result;
        double c = cos(x.f);
        double s = -sin(x.f);
        result.f = c;
        result.fx = s * x.fx;
        result.fy = s * x.fy;
        result.fxx = -c * x.fx * x.fx + s * x.fxx;
        result.fxy = -c * x.fx * x.fy + s * x.fxy;
        result.fyy = -c * x.fy * x.fy + s * x.fyy;
        return result;
    }

    friend FAD exp(const FAD& x) {
        FAD result;
        double e = exp(x.f);
        result.f = e;
        result.fx = e * x.fx;
        result.fy = e * x.fy;
        result.fxx = e * (x.fx * x.fx + x.fxx);
        result.fxy = e * (x.fx * x.fy + x.fxy);
        result.fyy = e * (x.fy * x.fy + x.fyy);
        return result;
    }
};

int main() {
    cout.precision(15);
    cout << fixed;
    int M;
    cin >> M;

    double points[M][2];
    for (int i = 0; i < M; i++) {
        cin >> points[i][0] >> points[i][1];
    }

    for (int i = 0; i < M; i++) {
        double x_val = points[i][0];
        double y_val = points[i][1];

        FAD x(x_val, true);
        FAD y(y_val, false);
        FAD F = inputFunction<FAD>(x, y);

        cout << F.getF() << " ";
        cout << F.getFx() << " ";
        cout << F.getFy() << " ";
        cout << F.getFxx() << " ";
        cout << F.getFxy() << " ";
        cout << F.getFyy() << endl;
    }

    return 0;
}