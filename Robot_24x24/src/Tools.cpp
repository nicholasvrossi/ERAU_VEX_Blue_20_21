#include <cstdint>
#include <cmath>
#include "main.h"
#include "Tools.hpp"


template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

int64_t ipow(int64_t base, unsigned int exp) {
    int64_t result = 1;

    while (exp) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}
