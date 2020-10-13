// motor_def.cpp 24x24 robot

#include "main.h"
#include "motor_def.hpp"

// Initialize controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Define and initialize motors
pros::Motor frontLeft(MOTOR_FRONT_LEFT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      false,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor frontRight(MOTOR_FRONT_RIGHT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      true,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor backLeft(MOTOR_BACK_LEFT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      false,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor backRight(MOTOR_BACK_RIGHT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      true,
                      pros::E_MOTOR_ENCODER_COUNTS);

//extern pros::MotorSet driveMotors;
