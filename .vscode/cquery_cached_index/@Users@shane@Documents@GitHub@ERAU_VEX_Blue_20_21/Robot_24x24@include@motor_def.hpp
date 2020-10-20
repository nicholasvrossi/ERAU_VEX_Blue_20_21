// motor_def.hpp 24x24 robot
#ifndef _MOTOR_DEF_HPP_
#define _MOTOR_DEF_HPP_
#include "main.h"
#include "../../G_inc/headers/AbstractMovement.hpp"

// Define the four drive motors
#define MOTOR_FRONT_LEFT_PORT (1)
#define MOTOR_FRONT_RIGHT_PORT (2)
#define MOTOR_BACK_LEFT_PORT (3)
#define MOTOR_BACK_RIGHT_PORT (4)
#define MOTOR_INTAKE_LEFT_PORT (6)
#define MOTOR_INTAKE_RIGHT_PORT (7)

// Prototype controller initialization function
extern pros::Controller master;

// Prototype motor defining functions
extern pros::Motor frontLeft; // front left motor

extern pros::Motor frontRight;  // front right motor

extern pros::Motor backLeft; // back left motor

extern pros::Motor backRight;  // back right

extern pros::Motor inLeft;  // back right

extern pros::Motor inRight;  // back right

extern pros::MotorSet Intake;

#endif //_MOTOR_DEF_HPP_
