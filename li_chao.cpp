#include <bits/stdc++.h>
using namespace std;

struct line {
    double a, b;

    line() : a(0), b(HUGE_VAL) {}

    line(double A, double B) : a(A), b(B) {}

    double operator()(double x) { return a * x + b; }
};

class li_chao {
    int n;
    vector<line> buf;

  public:
    li_chao(int N) : n(max(1, 1 << (int)(ceil(log2(N))))), buf(2 * n) {}

    void update(line l) {
        int i = 1, st = 0, step = n / 2;

        if (l(step) < buf[i](step))
            swap(l, buf[i]);

        while (i < n) {
            if ((l(st) < buf[i](st)) != (l(st + step) < buf[i](st + step)))
                i = 2 * i;
            else {
                st += step;
                i = 2 * i + 1;
            }

            step /= 2;

            if (l(st + step) < buf[i](st + step))
                swap(l, buf[i]);
        }
    }

    line query(int x) {
        line l;

        for (int i = x + n; i > 0; i /= 2)
            if (l(x) > buf[i](x))
                l = buf[i];

        return l;
    }
};
