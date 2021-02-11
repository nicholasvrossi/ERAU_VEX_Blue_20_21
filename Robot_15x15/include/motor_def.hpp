// motor_def.hpp 15x15 robot

#ifndef _MOTOR_DEF_HPP_
#define _MOTOR_DEF_HPP_
#include "main.h"
#include "AbstractMovement.hpp"

#define IS_RED (1)

// Define the four drive motors
#define MOTOR_FRONT_LEFT_PORT (1)
#define MOTOR_FRONT_RIGHT_PORT (2)
#define MOTOR_BACK_LEFT_PORT (10)
#define MOTOR_BACK_RIGHT_PORT (8)

// intake motors
#define MOTOR_INTAKE_LEFT_PORT  (4)
#define MOTOR_INTAKE_RIGHT_PORT (3)
#define INTAKE_SPEED  (127)
#define OUTTAKE_SPEED (-INTAKE_SPEED)
#define LAUNCH_SPEED  (127)

// Launcher motors
#define MOTOR_LAUNCHER_ANGLE (5)
#define MOTOR_LAUNCHER_LEFT_SHOOTER (9)
#define MOTOR_LAUNCHER_RIGHT_SHOOTER (6)

// Prototype controller initialization function
extern pros::Controller master;

// Prototype motor defining functions
extern pros::Motor frontLeft; // front left motor

extern pros::Motor frontRight; // front right motor

extern pros::Motor backLeft; // back left motor

extern pros::Motor backRight; // back right

extern pros::Motor inLeft;  // back right

extern pros::Motor inRight;  // back right

extern pros::MotorSet Intake;

extern pros::Motor launchAngle; // launcher angle motor

extern pros::Motor shootLeft; // left shooter motor

extern pros::Motor shootRight; // Right shooter motor


#endif //_MOTOR_DEF_HPP_
