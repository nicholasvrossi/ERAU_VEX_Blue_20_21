// motor_def.hpp 24x24 robot
#ifndef _MOTOR_DEF_HPP_
#define _MOTOR_DEF_HPP_
#include "main.h"
#include "../../G_inc/headers/AbstractMovement.hpp"

#define IS_RED (1)

// Define the four drive motors
#define MOTOR_FRONT_LEFT_PORT  (1)
#define MOTOR_FRONT_RIGHT_PORT (2)
#define MOTOR_BACK_LEFT_PORT   (3)
#define MOTOR_BACK_RIGHT_PORT  (4)
// intake motors
#define MOTOR_INTAKE_LEFT_PORT  (6)
#define MOTOR_INTAKE_RIGHT_PORT (7)
// lift motors
#define MOTOR_LIFT_LEFT_PORT  (8)
#define MOTOR_LIFT_RIGHT_PORT (9)
#define MOTOR_EJECTOR_PORT    (10)

#define INTAKE_SPEED  (127)
#define OUTTAKE_SPEED (-INTAKE_SPEED)
#define LIFT_UP_SPEED (127)
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

extern pros::MotorSet Intake;

extern pros::Motor liftLeft;

extern pros::Motor liftRight;

extern pros::Motor ejector;

extern pros::MotorSet LiftSet;

extern pros::ADIAnalogIn colorSensor;

#endif //_MOTOR_DEF_HPP_
