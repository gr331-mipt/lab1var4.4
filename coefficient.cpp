//
// Created by altair on 13.09.15.
//

#include <values.h>
#include <assert.h>
#include <string.h>
#include "coefficient.h"

bool Coefficient::setCoefficient(size_t index, mydouble value) {
    if(index < this->len) {
        this->val[index] = value;
        return true;
    }
    return false;
}

mydouble Coefficient::getMax(size_t min_index , size_t max_index) const {
    if(min_index > max_index) {
        size_t c = max_index;
        max_index = min_index;
        min_index = c;
    }
    if(max_index >= len) {
        max_index = len - 1;
    }
    mydouble max = std::abs(val[0]);
    for (size_t i = min_index; i <= max_index; i++) {
        if(max < std::abs(val[i])) {
            max = std::abs(val[i]);
        }
    }
    return max;
}

mydouble Coefficient::getMax() const {
    return getMax(0, len);
}

Coefficient Coefficient::getDerive() const {
    if(len == 0) {
        return Coefficient(0);
    }
    Coefficient ret(len - 1);
    for (size_t i = 0; i < len - 1; ret.val[i] = (len - i - 1) * val[i], i++);
    return ret;
}

mydouble Coefficient::f(mydouble c) const {
    mydouble k = 1;
    mydouble result = 0;
    for (long i = len - 1; i >= 0; i--, k *= c) {
        mydouble a = k * val[i];
        result += (mydouble)a;
    }
    return (mydouble)result;
}

Coefficient::Coefficient(const Coefficient &c) : Coefficient(c.len) {
    for(size_t i = 0; i < c.len; i++) {
        val[i] = c.getVal(i);
    }
}

void Coefficient::addCoefficient(const size_t index, const mydouble value) {
    assert(index < len);
    this->val[index] += value;
}
