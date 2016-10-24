//
// Created by altair on 13.09.15.
//

#ifndef ZADACHA1VAR4_4_COEFFICIENT_H
#define ZADACHA1VAR4_4_COEFFICIENT_H


#include <glob.h>
#include <stddef.h>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "mytypes.h"

class Coefficient {
protected:
    size_t len;
    mydouble *val;
public:

    Coefficient(const size_t len) : len(len) {
        val = new mydouble[len];
    }


    Coefficient(const Coefficient &c);

    ~Coefficient() {
        delete[] this->val;
        len = 0;
    }


    bool setCoefficient(size_t index, mydouble value);

    friend std::ostream &operator<<(std::ostream &o, const Coefficient &c) {
        std::streamsize prec = o.precision();
        o.precision(7);
        for (size_t i = 0; i < c.len; i++) {
            o << "a" << i << "= " << c.val[i] << std::endl;
        }
        o.precision(prec);
        return o;
    }

    mydouble getMax(size_t min_index, size_t max_index) const;
    mydouble getMax() const;


    size_t getLen() const {
        return len;
    }


    mydouble getVal(size_t index) const {
        if(index >= len)
            throw std::invalid_argument("invalid index");
        return val[index];
    }

    Coefficient getDerive() const;

    void addCoefficient(const size_t index, const mydouble value);

    mydouble f(mydouble c) const;
};


#endif //ZADACHA1VAR4_4_COEFFICIENT_H
