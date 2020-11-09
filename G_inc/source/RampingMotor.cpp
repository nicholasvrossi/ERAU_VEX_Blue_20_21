#include <vector>
#include <cstdint>
#include <algorithm>
#include "main.h"
#include "../headers/RampingMotor.hpp"
#include "../headers/Tools.hpp"


void pros::RampingMotor::setup(float rampStep) {
    this->rampStep = rampStep;
    this->currentSpeed = 0;
}


pros::RampingMotor::RampingMotor(const std::uint8_t port,
                                 const pros::motor_gearset_e_t gearset,
                                 bool reverse,
                                 pros::motor_encoder_units_e_t encoder_units,
                                 float rampStep)
                                 : pros::Motor(port, gearset, reverse, encoder_units) {
    setup(rampStep);
 }
pros::RampingMotor::RampingMotor(const std::uint8_t port,
                                 const pros::motor_gearset_e_t gearset,
                                 const bool reverse,
                                 float rampStep)
                                 : pros::Motor(port, gearset, reverse) {
    setup(rampStep);
}
pros::RampingMotor::RampingMotor(const std::uint8_t port,
                                 const pros::motor_gearset_e_t gearset,
                                 float rampStep)
                                 : pros::Motor(port, gearset) {
    setup(rampStep);
}
pros::RampingMotor::RampingMotor(const std::uint8_t port,
                                 const bool reverse,
                                 float rampStep)
                                 : pros::Motor(port, reverse) {
    setup(rampStep);
}
pros::RampingMotor::RampingMotor(const std::uint8_t port,
                                 float rampStep)
                                 : pros::Motor(port) {
    setup(rampStep);
}


std::int32_t pros::RampingMotor::move(const std::int32_t voltage)  {
    std::int32_t targetSpeed = std::clamp((int) voltage, -127, 127);

    int targetDisplacement = targetSpeed - currentSpeed;
    int targetDirection = 0;

    if (targetDisplacement != 0) {
        int targetDistance = std::abs(targetDisplacement);
        if (targetDistance < rampStep) {
            this->currentSpeed = targetSpeed;
        }
        else {
            targetDirection = sign(targetDisplacement);
            this->currentSpeed += targetDirection * rampStep;
        }
        move(currentSpeed);
    }

    return 1;
}
