#ifndef _GAUSSIAN_Movement_HPP_
#define _GAUSSIAN_Movement_HPP_

#include <cstdint>
#include "main.h"
#include "AbstractMovement.hpp"


struct GaussianConstants {
    int amplitude = 127; // should always be 127 (max power to motor)
    int minimum   = 10; // change if min speed does not move motor
    int base      = 2; // should not need to be changed
    int stretch   = 1000; // change to minimize time spent going at min power
    int shift     = 50; // set to larger number if no enough grainularity
    int n         = 4; // controls how quickly speed will increase/ decrease (higher = faster)
};

class GaussianMovement: public AbstractMovement {
  private:
    GaussianConstants consts;


    int mapGaussian(int x);

  public:
    void run();

    GaussianMovement* setConsts(GaussianConstants consts);
};

#endif // _GAUSSIAN_Movement_HPP_
