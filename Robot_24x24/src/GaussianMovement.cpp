#include <cstdint>
#include "main.h"
#include "GaussianMovement.hpp"
#include "Tools.hpp"

#define GAUSSIAN_MIN_ACCEPTABLE_ERROR (0)


int GaussianMovement::mapGaussian(int x) {
    const int64_t _STRETCH = ipow(consts.stretch, consts.n);
    const int _2N = 2 * consts.n;
    const int _SCALE = consts.amplitude - consts.minimum;
    const int _X_SHIFT = x - consts.shift;

    // ([scale] - [min]) * [base]^(-(x - [shift])^[2n] / [stretch]^[n]) + [min]
    return _SCALE * pow(consts.base, -(double) ipow(_X_SHIFT, _2N) / _STRETCH) + consts.minimum;
    // for Desmos: \left(a-m\right)b^{-\frac{\left(x-s_{shift}\right)^{2n}}{s_{stretch}^{n}}}+m
}


void GaussianMovement::run() {
    /*******************\
    | start itterations |
    \*******************/
    bool runIteration = true;
    while (runIteration) {
        for (auto motorTarget: motorTargets) {
            pros::Motor motor = motorTarget.first;
            int64_t target = motorTarget.second;
            int64_t error = target - motor.get_position();

            if (std::abs(error) > GAUSSIAN_MIN_ACCEPTABLE_ERROR) {
                // ratio (error / target) of the range of the gaussian (2*shift)
                motor.move_velocity((2*consts.shift) * (error / target));
            }
            else { // at target
                runIteration = false;
                motor.move_velocity(0);
            }
        }
    }


    /*****************\
    | stop all motors |
    \*****************/
    for (auto motorTarget: motorTargets) {
        pros::Motor motor = motorTarget.first;
        motor.move(0);
    }
}

GaussianMovement* GaussianMovement::setConsts(GaussianConstants consts) {
    this->consts = consts;
    return this;
}
