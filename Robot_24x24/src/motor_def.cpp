#include "motor_def.hpp"
#include "main.h"
#include "../../G_inc/headers/InvKinematics.hpp"

pros::Controller master = pros::Controller(pros::E_CONTROLLER_MASTER);


pros::Motor frontLeft = pros::Motor(MOTOR_FRONT_LEFT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      false,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor frontRight = pros::Motor(MOTOR_FRONT_RIGHT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      true,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor backLeft = pros::Motor(MOTOR_BACK_LEFT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      false,
                      pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor backRight = pros::Motor(MOTOR_BACK_RIGHT_PORT,
                      pros::E_MOTOR_GEARSET_18,
                      true,
                      pros::E_MOTOR_ENCODER_COUNTS);


pros::MotorSet driveMotors{
  frontLeft,
  frontRight,
  backLeft,
  backRight
};
