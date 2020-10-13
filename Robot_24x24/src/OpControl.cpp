#include "motor_def.hpp"
#include "../../G_inc/source/InvKinematics.cpp"
#include "main.h"
#include "math.h"

#define SLOW_BUTTON (pros::E_CONTROLLER_DIGITAL_L2)

void opcontrol() {
  float XL = 0;
  float YL = 0;
  float XR = 0;

  float FL_speed = 0;
  float FR_speed = 0;
  float BL_speed = 0;
  float BR_speed = 0;

	while (true) {
    InvKinematics bazinga;

    // Strafe Drive
    XL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    YL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    XR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    XL = pow((XL/127),3) * 127;
    YL = pow((YL/127),3) * 127;
    XR = pow((XR/127),3) * 127;


    FL_speed = XL+YL+XR;
    FR_speed = (-1*XL)+YL-XR;
    BL_speed = (-1*XL)+YL+XR;
    BR_speed = XL+YL-XR;

    if(master.get_digital(SLOW_BUTTON)){
      FL_speed = FL_speed/2;
      FR_speed = FR_speed/2;
      BL_speed = BL_speed/2;
      BR_speed = BR_speed/2;
    }

    bazinga.hold(frontLeft, FL_speed);
    bazinga.hold(frontRight, FR_speed);
    bazinga.hold(backLeft, BL_speed);
    bazinga.hold(backRight, BR_speed);
	}
}
