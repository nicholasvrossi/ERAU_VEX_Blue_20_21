#include <vector>
#include <cstdint>
#include <algorithm>
#include "main.h"
#include "PIDMovement.hpp"


PIDMovement::PIDVariables::PIDVariables(int64_t lastError) {
    this->lastError  = lastError;
    this->integral   = 0;
    this->derivative = 0;
}


void PIDMovement::run() {
    std::vector<PIDVariables*> vars;

    /**************\
    | set all data |
    \**************/
    for (auto motorTarget: motorTargets) {
        int64_t target = motorTarget.second;
        vars.push_back(new PIDVariables(target));
    }


    /*******************\
    | start itterations |
    \*******************/
    bool errorAtZero;
    bool derivativeAtZero;
    uint32_t timestamp = pros::millis();
    do {
        uint32_t deltaTime;
        while ((deltaTime = pros::millis() - timestamp) == 0); // wait until deltaTime is not zero
        timestamp = pros::millis();

        // run PID on all motors
        int i = 0;
        for (auto motorTarget: motorTargets) {
            pros::Motor motor = motorTarget.first;
            int64_t target = motorTarget.second;

            // proportion
        	int64_t error = target - motor.get_position();
            errorAtZero = error == 0;

            // integral
        	if (errorAtZero || std::abs(error) > consts.integralActiveRange)
        		vars[i]->integral = 0;
            else
                vars[i]->integral += error * deltaTime;

            // derivative
        	vars[i]->derivative = (error - vars[i]->lastError) / deltaTime;
        	vars[i]->lastError = error;
            derivativeAtZero = vars[i]->derivative == 0;

            // set motor speed
        	int speed = consts.Kp * error +
                        consts.Ki * vars[i]->integral +
                        consts.Kd * vars[i]->derivative;
            speed = std::clamp(speed, -127, 127);
        	motor.move(speed);
            i++;
        }
    } while (!(errorAtZero && derivativeAtZero)); // break out when error and derivative are not at zero


    /*****************\
    | stop all motors |
    \*****************/
    for (auto motorTarget: motorTargets) {
        pros::Motor motor = motorTarget.first;
        motor.move(0);
    }
}

PIDMovement* PIDMovement::setConsts(PIDConstants consts) {
    this->consts = consts;
    return this;
}
