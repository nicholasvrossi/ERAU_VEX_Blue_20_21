// motor_def.hpp 15x15 robot

#ifndef _MOTOR_DEF_HPP_
#define _MOTOR_DEF_HPP_
#include "main.h"
#include "AbstractMovement.hpp"

#define IS_RED (1)

// Define the four drive motors
#define MOTOR_FRONT_LEFT_PORT (12)
#define MOTOR_FRONT_RIGHT_PORT (9)
#define MOTOR_BACK_LEFT_PORT (8)
#define MOTOR_BACK_RIGHT_PORT (5)
#define MOTOR_LEFT_AIM (14)

// intake motors
#define MOTOR_INTAKE_LEFT_PORT  (4)
#define MOTOR_INTAKE_RIGHT_PORT (2)
#define INTAKE_SPEED  (127)
#define OUTTAKE_SPEED (-INTAKE_SPEED)
#define AIM_SPEED  (127)
#define LAUNCH_SPEED  (127)
#define SHOOT_MAX (2010)

// Launcher motors
#define MOTOR_LAUNCHER_ANGLE_MAX (177)
#define MOTOR_LAUNCHER_ANGLE (13)
#define MOTOR_LAUNCHER_LEFT_SHOOTER (19)
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

extern pros::Motor launchAngleLeft;

extern pros::Motor shootLeft; // left shooter motor

extern pros::Motor shootRight; // Right shooter motor


#endif //_MOTOR_DEF_HPP_
