//
// Created by altair on 13.09.15.
//

#ifndef ZADACHA1VAR4_4_EQUATION_H
#define ZADACHA1VAR4_4_EQUATION_H


#include "coefficient.h"
#include "ListPoints.h"
#include "mytypes.h"

const mydouble eps = 1e-9;

class Equation {
    Coefficient coefficient;

    mydouble borderTop;
    mydouble borderBottom;


    ListPoints mapFromBorderWithStep(mydouble step) const;

    mydouble refineOneRoot(AppPoint point);

    bool invalidPoint = false;

public:
    inline static bool IS_ZERO(mydouble x) {
        return (-eps < x && x < eps);
    }

    Equation(const Coefficient &coefficient) : coefficient(coefficient), borderTop(0), borderBottom(0) { }


    virtual ~Equation() {
    }

    bool calcBorderLowAccurasity();


    mydouble getBorderTop() const {
        return borderTop;
    }

    mydouble getBorderBottom() const {
        return borderBottom;
    }

    ListPoints preSolve() const;

    std::list<mydouble> refineRoots(ListPoints &points);

    void print() {
        for(size_t i = 0; i < coefficient.getLen(); i++) {
            std::cout << "+(" << coefficient.getVal(i) << ")x^" << (coefficient.getLen() - 1 - i);
        }
        std::cout << std::endl;
    }
};


#endif //ZADACHA1VAR4_4_EQUATION_H
