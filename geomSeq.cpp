#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout.precision(10);
    cout << scientific;

    int N = 0;
    cin >> N;

    float input [N][2];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> input[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        float product = input[i][0];
        float sum = input[i][1];
        float b = cbrt(product);

        if ((1.0f - (sum/b)) * (1.0f - (sum/b)) - 4 < 0) {
            cout << float(0) << " " << float(0) << " " << float(0) << endl;
            continue;
        }

        float deltaSqrt = sqrt((1.0f - (sum/b)) * (1.0f - (sum/b)) - 4);

        float r1, r2;
        if ((1.0f - (sum/b)) >= 0) {
            r1 = (sum/b - 1.0f - deltaSqrt) / 2;
            r2 = 2 / (sum/b - 1.0f - deltaSqrt);
        } else {
            r2 = (sum/b - 1.0f + deltaSqrt) / 2;
            r1 = 2 / (sum/b - 1.0f + deltaSqrt);
        }

        if (b / r1 >= b * r1) {
            cout << b / r1 << " " << b << " " << b * r1 << endl;
        } else if (b / r2 >= b * r2) {
            cout << b / r2 << " " << b << " " << b * r2 << endl;
        } else {
            cout << float(0) << " " << float(0) << " " << float(0) << endl;
        }
    }

    return 0;
}