// OpControl.cpp 24x24 robot

#include "motor_def.hpp"
#include "../../G_inc/source/InvKinematics.cpp"
#include "main.h"
#include "math.h"

// Define button to be pressed that slows robot's speed
#define SLOW_BUTTON (pros::E_CONTROLLER_DIGITAL_L2)
// Define button to be pressed that starts intake collection of balls
#define INTAKE (pros::E_CONTROLLER_DIGITAL_R1)
#define INTAKE_SPEED (85)
// Define button to be pressed that starts outtake dispose of balls
#define OUTTAKE (pros::E_CONTROLLER_DIGITAL_R2)
#define OUTTAKE_SPEED (-85)

// Start op-control function
void opcontrol() {
  // Initialize variables for left joystick y/x-value and right joystick x-value
  float XL = 0;
  float YL = 0;
  float XR = 0;

  // Initialize variables for motor speeds
  float FL_speed = 0; // FL denotes front left motor
  float FR_speed = 0; // FR denotes front right motor
  float BL_speed = 0; // BL denotes back left motor
  float BR_speed = 0; // BR denotes back right motor

  // while loop used for maintaining opcontrol function
	while (true) {
    // Construct instance of InvKinematics class to use motor driving functions
    // found in the InvKinematics class.
    InvKinematics Motor_Drive;


    // Strafe Drive (Robot drive forward, backward, and strafes with left
    // joystick, and turns with right joystick x-values)
    XL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    YL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    XR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // Pass joystick values through a cubic function to provide smoother
    // driving operation
    XL = pow((XL/127),3) * 127;
    YL = pow((YL/127),3) * 127;
    XR = pow((XR/127),3) * 127;

    // Compute speeds of each drive motor of the robot
    FL_speed = XL+YL+XR;
    FR_speed = (-1*XL)+YL-XR;
    BL_speed = (-1*XL)+YL+XR;
    BR_speed = XL+YL-XR;

    // if the SLOW_BUTTON is pressed, then half the speed. This allows for fine
    // control of the robot.
    if(master.get_digital(SLOW_BUTTON)){
      FL_speed = FL_speed/2;
      FR_speed = FR_speed/2;
      BL_speed = BL_speed/2;
      BR_speed = BR_speed/2;
    }

    // Feed speed values to hold function, which moves the motors at given
    // speeds.
    Motor_Drive.hold(frontLeft, FL_speed);
    Motor_Drive.hold(frontRight, FR_speed);
    Motor_Drive.hold(backLeft, BL_speed);
    Motor_Drive.hold(backRight, BR_speed);

    // If buttons are pushed either collect or dispose of balls in the intake
    if(master.get_digital(INTAKE)){
      Motor_Drive.hold(Intake,INTAKE_SPEED);
    }
    else if(master.get_digital(OUTTAKE)){
      Motor_Drive.hold(Intake,OUTTAKE_SPEED);
    }
    else{
      Motor_Drive.hold(inLeft,0);
      Motor_Drive.hold(inRight,0);
    }
	}
}
