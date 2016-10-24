//
// Created by altair on 13.09.15.
//

#include "gasTask.h"
#include "Equation.h"

void gasTask::readValues() {
    cin >> g0;
    cin >> ro0;
    cin >> U0;
    cin >> P0;
    cin >> C0;
    cin >> g3;
    cin >> ro3;
    cin >> U3;
    cin >> P3;
    cin >> C3;
}

inline mydouble sqr(mydouble x) {
    return x * x;
}

Coefficient gasTask::getCoefficient() {
    if(Equation::IS_ZERO(P0) && Equation::IS_ZERO(P3)) {
        return getCoefficients122();
    }
    return getCoefficients121();
}

Coefficient gasTask::getCoefficients121() {
    mydouble V = U0 - U3;
    mydouble Vin2 = V * V;
    mydouble znam = ro0 * ro3 * Vin2;
    mydouble X = P3 / znam;
    mydouble h0 = (g0 + 1) / (g0 - 1);
    mydouble h3 = (g3 + 1) / (g3 - 1);
    mydouble a0 = ro0 * C0 * C0 * (h0 - 1);
    mydouble a3 = ro3 * C3 * C3 * (h3 - 1);
    mydouble b0 = a0 / znam;
    mydouble b3 = a3 / znam;
    mydouble d0 = (h0 - 1) * ro3;
    mydouble d3 = (h3 - 1) * ro0;
    mydouble e = P0 / znam;
    Coefficient ret(7);
    ret.setCoefficient(0, sqr(d0 * h3 - d3 * h0));
    ret.setCoefficient(1, 2 * (h3 * sqr(d0) * (b3 - h3 * e)
                               + h0 * sqr(d3) * (b0 - X * h0)
                               - h0 * h3 * (d0 * h3 + d3 * h0)
                               - d0 * d3 * (h0 * b3 + h3 * b0)
                               + d0 * d3 * h0 * h3 * (X + e) ));
    ret.setCoefficient(2,
                       sqr(h0 * h3)
                       + sqr(d0) * (sqr(h3 * e) + sqr(b3) - 4 * b3 * h3 * e )
                       + sqr(d3) * (sqr(b0) + sqr(h0 * X) - 4 * b0 * X * h0 )
                       - 2 * d0 * h3 * (2 * b3 * h0 + h3 * b0 - e * h0 * h3)
                       - 2 * d3 * h0 * (2 * b0 * h3 + h0 * b3 - h0 * h3 * X)
                       - 2 * d0 * d3 * (X * e * h0 * h3 + b0 * b3)
                       + 2 * d0 * d3 * (X + e) * (b3 * h0 + h3 * b0)
    );
    ret.setCoefficient(3,
                       2 * (
                               h0 * h3 * (b0 * h3 + b3 * h0)
                               + sqr(d0) * e * b3 * (h3 * e - b3)
                               + (X * h0 - b0) * sqr(d3) * b0 * X
                               - d0 * (h0 * sqr(b3) - e * b0 * sqr(h3))
                               - 2 * d0 * h3 * b3 * (b0 - e * h0)
                               - d3 * (h3 * sqr(b0) - X * b3 * sqr(h0))
                               - 2 * d3 * b0 * h0 * (b3 - X * h3)
                               - e * d0 * d3 * X * (h0 * b3 + h3 * b0)
                               + d0 * d3 * b0 * b3 * (X + e)
                       )
    );
    ret.setCoefficient(4,
                       sqr(b0 * h3) + sqr(b3 * h0) + 4 * b0 * b3 * h0 * h3
                       + sqr(d0 * b3 * e) + sqr(d3 * b0 * X)
                       - 2 * d0 * (b0 * sqr(b3) - e * sqr(b3) * h0 - 2 * e * h3 * b0 * b3)
                       - 2 * d3 * b0 * (b0 * (b3 - X * h3) - 2 * b3 * X * h0)
                       - 2 * e * d0 * d3 * b0 * b3 * X
    );
    ret.setCoefficient(5,
                       2 * (b0 * b3 * (b0 * h3 + b3 * h0) + b0 * b3 * (d0 * e * b3 + d3 * X * b0))
    );
    ret.setCoefficient(6,
                       sqr(b0 * b3)
    );
    return ret;
}

Coefficient gasTask::getCoefficients122() {
    cout << "coef 122" << endl;
    mydouble V = U0 - U3;
    mydouble Vin2 = V * V;
    mydouble znam = ro0 * Vin2;
    mydouble X = P3 / znam;
    mydouble h0 = (g0 + 1) / (g0 - 1);
    mydouble h3 = (g3 + 1) / (g3 - 1);
    mydouble a0 = ro0 * C0 * C0 * (h0 - 1);
    mydouble a3 = ro3 * C3 * C3 * (h3 - 1);
    mydouble b0 = a0 / znam;
    mydouble b3 = a3 / znam;
    mydouble e = ro3 / ro0;

    Coefficient ret(7);
    ret.setCoefficient(0, sqr((h0 - 1) * h3 * e - (h3 - 1) * h0));
    ret.setCoefficient(1,
        2 * ( sqr(h0 - 1) * sqr(e) * h3 * b3
              + sqr(h3 - 1) * h0 * b0
              - (h0 - 1) * sqr(e) * h0 * sqr(h3)
              - (h3 - 1) * e * sqr(h0) * h3
              - (h0 - 1) * (h3 - 1) * e * (b0 * h3 + h0 * b3)
            )
    );
    ret.setCoefficient(2,
        sqr(e * h0 * h3)
        + sqr((h0 - 1) * e * b3)
        + sqr((h3 - 1) * b0)
        - 2 * (h0 - 1) * sqr(e) * h3 * (b0 * h3 + 2 * h0 * b3)
        - 2 * (h3 - 1) * e * h0 * (h0 * b3 + 2 * h3 * b0)
        - 2 * (h0 - 1) * (h3 - 1) * e * b0 * b3
    );
    ret.setCoefficient(3,
        2 * (
                sqr(e) * h0 * h3 * (b0 * h3 + h0 * b3)
                - (h0 - 1) * sqr(e) * b3 * (b3 * h0 + 2 * h3 * b0)
                - (h3 - 1) * e * b0 * (h3 * b0 + 2 * h0 * b3)
            )
    );
    ret.setCoefficient(4,
        sqr(e) * (sqr(b0 * h3) + sqr(h0 * b3) + 4 * h0 * h3 * b0 * b3)
        - 2 * (h0 - 1) * sqr(e) * b0 * sqr(b3)
        - 2 * (h3 - 1) * e * b3 * sqr(b0)
    );
    ret.setCoefficient(5,
        2 * sqr(e) * b0 * b3 * (h0 * b3 + h3 * b0)
    );
    ret.setCoefficient(6,
        sqr(e * b0 * b3)
    );
    return ret;
}

void gasTask::printValues() {
    std::streamsize prec = cout.precision();
    cout.precision(7);
    cout << g0 << endl;
    cout << ro0 << endl;
    cout << U0 << endl;
    cout << P0 << endl;
    cout << C0 << endl;
    cout << g3 << endl;
    cout << ro3 << endl;
    cout << U3 << endl;
    cout << P3 << endl;
    cout << C3 << endl;
    cout.precision(prec);
}

mydouble gasTask::getAnswer(mydouble Y) {
    if(Equation::IS_ZERO(P0) && Equation::IS_ZERO(P3)) {
        return getAnswer122(Y);
    }
    return getAnswer121(Y);
}

mydouble gasTask::getAnswer122(mydouble Y) {
    mydouble V = U0 - U3;
    mydouble Vin2 = V * V;
    mydouble h0 = (g0 + 1) / (g0 - 1);
    mydouble h3 = (g3 + 1) / (g3 - 1);
    mydouble a0 = ro0 * C0 * C0 * (h0 - 1);
    mydouble a3 = ro3 * C3 * C3 * (h3 - 1);
    mydouble P1 = Y * ro0 * Vin2;
    mydouble ro1 = ro0 * (h0 * P1 + a0) / (a0 + P1);
    mydouble ro2 = ro3 * (h3 * P1 + a3) / (a3 + P1);
    D0 = U0 - sqrt((P0 - P1) / (sqr(ro0) / ro1 - ro0));
    D0_ = U0 + sqrt((P0 - P1) / (sqr(ro0) / ro1 - ro0));
    D3 = U3 - sqrt((P3 - P1) / (sqr(ro3) / ro2 - ro3));
    D3_ = U3 + sqrt((P3 - P1) / (sqr(ro3) / ro2 - ro3));
    return 0;
}

mydouble gasTask::getAnswer121(mydouble Y) {
    mydouble V = U0 - U3;
    mydouble Vin2 = V * V;
    mydouble h0 = (g0 + 1) / (g0 - 1);
    mydouble h3 = (g3 + 1) / (g3 - 1);
    mydouble a0 = ro0 * C0 * C0 * (h0 - 1);
    mydouble a3 = ro3 * C3 * C3 * (h3 - 1);
    mydouble P1 = Y * ro0 * ro3 * Vin2;
    mydouble ro1 = ro0 * (h0 * P1 - a0) / (a0 + P1);
    mydouble ro2 = ro3 * (h3 * P1 - a3) / (a3 + P1);
    D0 = U0 - sqrt((P0 - P1) / (sqr(ro0) / ro1 - ro0));
    D3 = U3 - sqrt((P3 - P1) / (sqr(ro3) / ro2 - ro3));
    D0_ = U0 + sqrt((P0 - P1) / (sqr(ro0) / ro1 - ro0));
    D3_ = U3 + sqrt((P3 - P1) / (sqr(ro3) / ro2 - ro3));
    return 0;
}

void gasTask::printAnswer() const {
    cout << "D0:" << D0 << endl;
    cout << "D3:" << D3 << endl;
    cout << "DO_:" << D0_ << endl;
    cout << "D3_:" << D3_ << endl;
}
