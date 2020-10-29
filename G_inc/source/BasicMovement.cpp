#include <cmath>
#include "BasicMovement.hpp"
#include "main.h"


void BasicMovement::run() {
    /*******************\
    | start itterations |
    \*******************/
    for (auto motorTarget: motorTargets) {
        pros::Motor motor = motorTarget.first;
        motor.move(consts.power);
    }


    double error;
    do {
        error = 0;
        for (auto motorTarget: motorTargets) {
            pros::Motor motor = motorTarget.first;
            int64_t target = motorTarget.second;

            error += target - motor.get_position();
        }
        error /= motorTargets.size();
    } while (abs(error) < consts.acceptableError);


    /**************\
    | apply breaks |
    \**************/
    double vel = 0;
    for (auto motorTarget: motorTargets) {
        pros::Motor motor = motorTarget.first;
        motor.move(-consts.power);
        vel += motor.get_actual_velocity();
    }
    vel /= motorTargets.size();

    /*****************\
    | stop all motors |
    \*****************/
    pros::delay(consts.timeConst * vel);

    /*****************\
    | stop all motors |
    \*****************/
    for (auto motorTarget: motorTargets) {
        pros::Motor motor = motorTarget.first;
        motor.move(0);
    }
}

BasicMovement* BasicMovement::setConsts(BasicConstants consts) {
    this->consts = consts;
    return this;
}
