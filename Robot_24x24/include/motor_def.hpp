// motor_def.hpp 24x24 robot
#ifndef _MOTOR_DEF_HPP_
#define _MOTOR_DEF_HPP_
#include "main.h"
#include "../../G_inc/headers/AbstractMovement.hpp"

#define IS_RED (1)

// Define the four drive motors
#define MOTOR_FRONT_LEFT_PORT  (13)
#define MOTOR_FRONT_RIGHT_PORT (2)
#define MOTOR_BACK_LEFT_PORT   (3)
#define MOTOR_BACK_RIGHT_PORT  (4)
// Turntable motors
#define MOTOR_TURNTABLE1_PORT (1)
#define MOTOR_TURNTABLE2_PORT (7)
// Pyrmid open and close motors
#define MOTOR_PYRM1_PORT  (8)
#define MOTOR_PYRM2_PORT  (9)
#define MOTOR_PYRM3_PORT   (10)
#define MOTOR_PYRM4_PORT     (11)

#define INTAKE_SPEED  (127)
#define OUTTAKE_SPEED (-INTAKE_SPEED)
#define LIFT_UP_SPEED (90)
#define LIFT_DN_SPEED (-LIFT_UP_SPEED)
#define EJECTOR_EJECT (LIFT_DN_SPEED)

// color sensor values for red and blue used in the ejector
#define BLUE_COLOR_MIN (0) // TODO check value
#define BLUE_COLOR_MAX (0) // TODO check value
#define RED_COLOR_MIN  (0) // TODO check value
#define RED_COLOR_MAX  (0) // TODO check value


// Prototype controller initialization function
extern pros::Controller master;

// Prototype motor defining functions
extern pros::Motor frontLeft; // front left motor

extern pros::Motor frontRight;  // front right motor

extern pros::Motor backLeft; // back left motor

extern pros::Motor backRight;  // back right

extern pros::Motor inLeft;  // back right

extern pros::Motor inRight;  // back right

extern pros::Motor Pyrm1;

extern pros::Motor Pyrm2;

extern pros::Motor Pyrm3;

extern pros::Motor Pyrm4;

extern pros::Motor TurnTable1;

extern pros::Motor TurnTable2;

extern pros::ADIAnalogIn colorSensor;

#endif //_MOTOR_DEF_HPP_
