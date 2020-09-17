#ifndef _RAMPING_MOTOR_HPP_
#define _RAMPING_MOTOR_HPP_

#include <vector>
#include <cstdint>
#include "main.h"

namespace pros {
class RampingMotor: public pros::Motor {
private:
    float currentSpeed;
    float rampStep;

    void setup(float rampStep);

public:
    RampingMotor(const std::uint8_t port,
                 const pros::motor_gearset_e_t gearset,
                 const bool reverse,
                 const pros::motor_encoder_units_e_t encoder_units,
                 float rampStep);
    RampingMotor(const std::uint8_t port,
                 const pros::motor_gearset_e_t gearset,
                 const bool reverse,
                 float rampStep);
    RampingMotor(const std::uint8_t port,
                 const pros::motor_gearset_e_t gearset,
                 float rampStep);
    RampingMotor(const std::uint8_t port,
                 const bool reverse,
                 float rampStep);
    RampingMotor(const std::uint8_t port,
                 float rampStep);


    std::int32_t move(const std::int32_t voltage);
};
}


#endif // _RAMPING_MOTOR_HPP_
