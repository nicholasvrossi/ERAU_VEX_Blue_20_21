// motor_def.cpp 15x15 robot

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

pros::Motor inLeft(MOTOR_INTAKE_LEFT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      true,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor inRight(MOTOR_INTAKE_RIGHT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      false,
                      pros::E_MOTOR_ENCODER_COUNTS);



pros::Motor launchAngle(MOTOR_LAUNCHER_ANGLE,
                      pros::E_MOTOR_GEARSET_18,
                      true,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor shootLeft(MOTOR_LAUNCHER_LEFT_SHOOTER ,
                      pros::E_MOTOR_GEARSET_18,
                      true,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor shoootRight(MOTOR_LAUNCHER_RIGHT_SHOOTER ,
                      pros::E_MOTOR_GEARSET_18,
                      false,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::MotorSet Intake = {inLeft,inRight};
