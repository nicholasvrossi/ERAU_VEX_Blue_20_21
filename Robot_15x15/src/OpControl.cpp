#include "motor_def.hpp"
#include "../../G_inc/source/InvKinematics.cpp"
#include "main.h"


void opcontrol() {
  int XL = 0;
  int YL = 0;
  int XR = 0;

  int FL_speed = 0;
  int FR_speed = 0;
  int BL_speed = 0;
  int BR_speed = 0;

	while (true) {
    InvKinematics bazinga;
    XL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    YL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    XR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    FL_speed = YL+XR;
    FR_speed = YL-XR;
    BL_speed = YL+XR;
    BR_speed = YL-XR;

    bazinga.hold(frontLeft, FL_speed);
    bazinga.hold(frontRight, FR_speed);
    bazinga.hold(backLeft, BL_speed);
    bazinga.hold(backRight, BR_speed);
	}
}
