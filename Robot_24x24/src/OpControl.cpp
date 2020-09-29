#ifndef _OPCONTROL_CPP_
#define _OPCONTROL_CPP_
#include "main.h"
#include "../../G_inc/headers/InvKinematics.hpp"
#include "motor_def.hpp"

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
#endif //_OPCONTROL_CPP_
