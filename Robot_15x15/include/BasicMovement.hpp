#ifndef _BASIC_MOVEMENT_HPP_
#define _BASIC_MOVEMENT_HPP_

#include "AbstractMovement.hpp"
#include "main.h"



// Ft = mv
// t = m/F * v
struct BasicConstants {
    double timeConst = 2.25; // calculate via {mass kg} / {max force of drive}
    int acceptableError = 20; // the maximum acceptable error
    int power = 127;// the power of the motors (in the positive direction)
    
};

class BasicMovement: public AbstractMovement {
  private:
    BasicConstants consts;

  public:
    void run();

    BasicMovement* setConsts(BasicConstants consts);
};

#endif // _BASIC_MOVEMENT_HPP_
