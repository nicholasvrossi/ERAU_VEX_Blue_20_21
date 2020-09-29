#ifndef _MOTOR_DEF_HPP_
#define _MOTOR_DEF_HPP_
#include "main.h"
#include "../../G_inc/headers/InvKinematics.hpp"

#define MOTOR_FRONT_LEFT_PORT (1)
#define MOTOR_FRONT_RIGHT_PORT (2)
#define MOTOR_BACK_LEFT_PORT (3)
#define MOTOR_BACK_RIGHT_PORT (4)

pros::Controller master;

pros::Motor frontLeft;

pros::Motor frontRight;

pros::Motor backLeft;

pros::Motor backRight;

pros::MotorSet driveMotors;

#endif //_MOTOR_DEF_HPP_
