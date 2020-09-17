#ifndef _TOOLS_HPP_
#define _TOOLS_HPP_

#include <cstdint>
#include "main.h"


// returns the sign of the input
template <typename T> int sign(T val);

// returns the {exp}th positive interger power of the base using the exponentiation
//  by squaring method
int64_t ipow(int64_t base, unsigned int exp);


#endif // _TOOLS_HPP_
