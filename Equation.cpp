//
// Created by altair on 13.09.15.
//

#include "Equation.h"
#include "ListPoints.h"
#include <cmath>

bool Equation::calcBorderLowAccurasity() {
    mydouble A = coefficient.getMax(1, coefficient.getLen());
    mydouble B = coefficient.getMax(0, coefficient.getLen() - 2);
    mydouble an = std::abs(coefficient.getVal(coefficient.getLen() - 1));
    mydouble a0 = std::abs(coefficient.getVal(0));

    if(IS_ZERO(a0) || IS_ZERO(an + B)) {
        return false;
    }
    borderTop = 1 + A / a0;
    borderBottom = an / (an + B);
    return true;
}

ListPoints Equation::mapFromBorderWithStep(mydouble step) const {
    ListPoints listPoints;
    bool lastSign = coefficient.f(borderBottom) > 0;
    for(mydouble i = borderBottom + step; i <= borderTop; i += step) {
        bool nowSign = coefficient.f(i) > 0;
        if(nowSign != lastSign) {
            listPoints.push_back(AppPoint(i - step, i));
        }
        lastSign = nowSign;
    }
    lastSign = coefficient.f(-borderTop) > 0;
    for(mydouble i = -borderTop + step; i <= -borderBottom; i += step) {
        bool nowSign = coefficient.f(i) > 0;
        if(nowSign != lastSign) {
            listPoints.push_back(AppPoint(i - step, i));
        }
        lastSign = nowSign;
    }
    return listPoints;
}

ListPoints Equation::preSolve() const {
    mydouble N = (borderTop - borderBottom) / 2000;
    ListPoints listPoints = mapFromBorderWithStep(N);
    while(listPoints.size() < coefficient.getLen() - 1 && N > 1e-6 ) {
        N /= 2;
        listPoints = mapFromBorderWithStep(N);
    }
    return listPoints;
}

std::list<mydouble> Equation::refineRoots(ListPoints &points) {
    std::list<mydouble> list;
    for(ListPoints::iterator i = points.begin(); i != points.end(); ++i) {
        if(!invalidPoint) {
            list.push_back(refineOneRoot(*i));
        } else {
            invalidPoint = false;
        }
    }
    return list;
}

mydouble Equation::refineOneRoot(AppPoint point) {
    if(IS_ZERO(coefficient.f(point.left)))
        return point.left;
    if(IS_ZERO(coefficient.f(point.right)))
        return point.right;
    mydouble p = (point.left + point.right) / 2;
    mydouble val = coefficient.f(p);
    //!IS_ZERO(val) &&
    while(!IS_ZERO(point.left - point.right)) {
        if(val > 0) {
            if(coefficient.f(point.right) > 0) {
                point.right = p;
            } else {
                point.left = p;
            }
        } else {
            if(coefficient.f(point.left) < 0) {
                point.left = p;
            } else {
                point.right = p;
            }
        }
        p = (point.left + point.right) / 2;
        val = coefficient.f(p);
    }
    /*
    if(!IS_ZERO(val)) {
        invalidPoint = true;
    }
     */
    return p;
}
