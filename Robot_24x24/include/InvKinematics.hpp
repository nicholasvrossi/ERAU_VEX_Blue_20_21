#ifndef _INV_KINEMATICS_HPP_
#define _INV_KINEMATICS_HPP_

#include <vector>
#include <functional>
#include <cstdint>
#include "main.h"
#include "AbstractMovement.hpp"


class InvKinematics {
  private:
    std::vector<std::function<void()>> commands;

    void addAndRunCommand(std::function<void()> funct);

  public:
    // runs the Movement algorithm provided
    InvKinematics* move(AbstractMovement* command);

    // basically a wrapper for pros::delay()
    InvKinematics* delay(int64_t millis);

    // applies constant power to the specified motor(s)
    InvKinematics* hold(pros::Motor motor, int velocity);
    InvKinematics* hold(pros::MotorSet motors, int velocity);

    // stops applying power to the specified motor(s)
    InvKinematics* stop(pros::Motor motor);
    InvKinematics* stop(pros::MotorSet motors);

    // applies constant power to the specified motor(s) for the specified amount of time
    InvKinematics* pulse(pros::Motor motor, int velocity, int duration);
    InvKinematics* pulse(pros::MotorSet motors, int velocity, int duration);

    // resets the position of the specified motor(s)
    InvKinematics* tare(pros::Motor motor);
    InvKinematics* tare(pros::MotorSet motors);
};


#endif // _INV_KINEMATICS_HPP_
