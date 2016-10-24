//
// Created by altair on 13.09.15.
//

#ifndef ZADACHA1VAR4_4_GASTASK_H
#define ZADACHA1VAR4_4_GASTASK_H


#include <iostream>
#include "coefficient.h"
#include "mytypes.h"

using std::cin;
using std::cout;
using std::endl;

class gasTask {

    mydouble g0;
    mydouble ro0;
    mydouble U0;
    mydouble P0;
    mydouble C0;

    mydouble g3;
    mydouble ro3;
    mydouble U3;
    mydouble P3;
    mydouble C3;

    mydouble D0;
    mydouble D0_;
    mydouble D3;
    mydouble D3_;

    Coefficient getCoefficients121();
    Coefficient getCoefficients122();

    mydouble getAnswer121(mydouble Y);
    mydouble getAnswer122(mydouble Y);

public:

    gasTask() {
        g0 = ro0 = U0 = P0 = C0 = 0;
        g3 = ro3 = U3 = P3 = C3 = 0;
    }

    void readValues();

    Coefficient getCoefficient();
    mydouble getAnswer(mydouble Y);

    void printValues();
    void printAnswer() const;
};


#endif //ZADACHA1VAR4_4_GASTASK_H
