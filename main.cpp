#include <iostream>
#include "gasTask.h"
#include "Equation.h"
#include "mytypes.h"

using namespace std;

int main() {
    gasTask gt;
    cout.precision(12);
    gt.readValues();
    cout << "#Input:" << endl;
    gt.printValues();
    Coefficient c = gt.getCoefficient();
    //cout << c.f(0) << endl;
    cout << "#Coefficients:" << endl << c;
    Equation eq(c);
    if(eq.calcBorderLowAccurasity()) {
        cout << "#Borders:" << endl;
        cout << "top: " << eq.getBorderTop() << endl
        << "bottom: " << eq.getBorderBottom() << endl;
    }
    ListPoints listPoints = eq.preSolve();
    cout << "#First version of roots" << endl;
    for(ListPoints::iterator i = listPoints.begin(); i != listPoints.end(); ++i) {
        cout << "l:" << i->left << " r: " << i->right << " vl:" << c.f(i->left) << " vr:" << c.f(i->right) <<endl;
    }
    std::list<mydouble> roots = eq.refineRoots(listPoints);
    cout << "#Roots:" << endl;
    for(std::list<mydouble>::iterator i = roots.begin(); i != roots.end(); ++i) {
        cout << *i << " val:" << c.f(*i) << endl;
    }
    cout << "#Equation:" << endl;
    eq.print();
    cout << "#D1 & D2" << endl;
    for(std::list<mydouble>::iterator i = roots.begin(); i != roots.end(); ++i) {
        if(*i < 0)
            continue;
        gt.getAnswer(*i);
        gt.printAnswer();
    }
    return 0;
}