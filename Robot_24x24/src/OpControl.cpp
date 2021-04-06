// OpControl.cpp 24x24 robot

#include "motor_def.hpp"
#include "../../G_inc/source/InvKinematics.cpp"
#include "main.h"
#include "math.h"


// turn the turntable to the Right
#define TURNTABLE_RIGHT (pros::E_CONTROLLER_DIGITAL_R1)
// Open the pyryrmid
#define OPENPYRM (pros::E_CONTROLLER_DIGITAL_R2)
// turn the turntable to the Left
#define TURNTABLE_LEFT (pros::E_CONTROLLER_DIGITAL_L1)
// Close the pyryrmid
#define CLOSEPYRM (pros::E_CONTROLLER_DIGITAL_L2)


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

  InvKinematics Motor_Drive;

  int ballColor = 0;

  // while loop used for maintaining opcontrol function
	while (true) {
        // Construct instance of InvKinematics class to use motor driving functions
        // found in the InvKinematics class.

        // Strafe Drive (Robot drive forward, backward, and strafes with left
        // joystick, and turns with right joystick x-values)
        XL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        YL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        XR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // Pass joystick values through a cubic function to provide smoother
        // driving operation
        XL = std::pow((XL/127),3) * 127;
        YL = std::pow((YL/127),3) * 127;
        XR = std::pow((XR/127),3) * 127;

        // Compute speeds of each drive motor of the robot
        FL_speed = XL+YL+XR;
        FR_speed = (-1*XL)+YL-XR;
        BL_speed = (-1*XL)+YL+XR;
        BR_speed = XL+YL-XR;


        // Feed speed values to hold function, which moves the motors at given
        // speeds.
        Motor_Drive.hold(frontLeft, FL_speed);
        Motor_Drive.hold(frontRight, FR_speed);
        Motor_Drive.hold(backLeft, BL_speed);
        Motor_Drive.hold(backRight, BR_speed);

        // If buttons are pushed either open or close pyryrmid
        if(master.get_digital(OPENPYRM)){
          // Motor_Drive.hold(inLeft,INTAKE_SPEED * 0.67);
          // Motor_Drive.hold(inRight,INTAKE_SPEED * 0.67);
          Motor_Drive.hold(Pyrm1,INTAKE_SPEED);
          Motor_Drive.hold(Pyrm2,INTAKE_SPEED);
          Motor_Drive.hold(Pyrm3,INTAKE_SPEED);
          Motor_Drive.hold(Pyrm4,INTAKE_SPEED);
        }
        else if(master.get_digital(CLOSEPYRM)){
          // Motor_Drive.hold(inLeft,OUTTAKE_SPEED * 0.67);
          // Motor_Drive.hold(inRight,OUTTAKE_SPEED * 0.67);
          Motor_Drive.hold(Pyrm1,OUTTAKE_SPEED);
          Motor_Drive.hold(Pyrm2,OUTTAKE_SPEED);
          Motor_Drive.hold(Pyrm3,OUTTAKE_SPEED);
          Motor_Drive.hold(Pyrm4,OUTTAKE_SPEED);
        }
        else{
          Motor_Drive.hold(Pyrm1,0);
          Motor_Drive.hold(Pyrm2,0);
          Motor_Drive.hold(Pyrm3,0);
          Motor_Drive.hold(Pyrm4,0);
        }

        // If buttons are pushed either open or close pyryrmid
        if(master.get_digital(TURNTABLE_RIGHT)){
          // Motor_Drive.hold(inLeft,INTAKE_SPEED * 0.67);
          // Motor_Drive.hold(inRight,INTAKE_SPEED * 0.67);
          Motor_Drive.hold(TurnTable1,INTAKE_SPEED);
          Motor_Drive.hold(TurnTable2,INTAKE_SPEED);
        }
        else if(master.get_digital(TURNTABLE_LEFT)){
          // Motor_Drive.hold(inLeft,OUTTAKE_SPEED * 0.67);
          // Motor_Drive.hold(inRight,OUTTAKE_SPEED * 0.67);
          Motor_Drive.hold(TurnTable1,OUTTAKE_SPEED);
          Motor_Drive.hold(TurnTable2,OUTTAKE_SPEED);
        }

        else{
          Motor_Drive.hold(TurnTable1,0);
          Motor_Drive.hold(TurnTable2,0);
        }


      }
}
