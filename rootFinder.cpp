#include <cmath>
using namespace std;

double findZero (double (*f)(double), double a, double b, int M, double eps, double delta) {
    double fa = f(a);
    double fb = f(b);
    double e = b - a;
    int count = 2;

    if (fa * fb <= 0 && count < M) {
        while (count < M) {
            e = e / 2;
            double c = a + e;
            double fc = f(c);
            if (fabs(e) < delta || fabs(fc) < eps) {
                return c;
            }
            if (fabs(e) < 0.1) {
                break;
            }
            if (fc * fa <= 0) {
                b = c;
                fb = fc;
            } else {
                a = c;
                fa = fc;
            }
            count++;
        }
    }

    double x0 = a;
    double x1 = b;
    double fx0 = fa;
    double fx1 = fb;
    double x = x1;
    while (count < M) {
        x = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        double fx = f(x);
        if (fabs(fx) < eps || fabs(x - x1) < delta) {
            return x;
        }
        x0 = x1;
        fx0 = fx1;
        x1 = x;
        fx1 = fx;
        count++;
    }
    return x;
}