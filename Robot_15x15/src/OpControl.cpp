#include "motor_def.hpp"
#include "../../G_inc/source/InvKinematics.cpp"
#include "main.h"


void opcontrol() {
  int XL = 0;
  int YL = 0;
  int XR = 0;



	while (true) {
    InvKinematics bazinga;
    XL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    YL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    XR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    bazinga.hold(frontLeft, XL+YL+XR);
    bazinga.hold(frontRight, (-1*XL)+YL-XR);
    bazinga.hold(backLeft, (-1*XL)+YL+XR);
    bazinga.hold(backRight, XL+YL-XR);
	}
}
