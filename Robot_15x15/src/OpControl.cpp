// OpControl.cpp 15x15 robot

#include "motor_def.hpp"
#include "InvKinematics.hpp"
#include "main.h"
#include "math.h"
#include <iostream>
#include <string>
using namespace std;

// Define button to be pressed that slows robot's speed
#define SLOW_BUTTON (pros::E_CONTROLLER_DIGITAL_B)
// Define button to be pressed that starts intake collection of balls
#define INTAKE (pros::E_CONTROLLER_DIGITAL_R1)
// Define button to be pressed that starts outtake dispose of balls
#define OUTTAKE (pros::E_CONTROLLER_DIGITAL_R2)

#define AIM (pros::E_CONTROLLER_DIGITAL_L1)

#define LOWER (pros::E_CONTROLLER_DIGITAL_L2)

#define DISP_ENCODERS (pros::E_CONTROLLER_DIGITAL_Y)
#define TARE_ENCODERS (pros::E_CONTROLLER_DIGITAL_X)

#define MANUAL_LOWER (pros::E_CONTROLLER_DIGITAL_DOWN)
#define AUTON (pros::E_CONTROLLER_DIGITAL_RIGHT)


char str1[30];
char str2[30];
char str3[30];
char str4[30];
char str5[30];

// initialize variables for storing encoder values
int encFR = 0;
int encFL = 0;
int encBR = 0;
int encBL = 0;
int encAIM = 0;
int encSR = 0;
int encSL = 0;
int shoot_goal = 0;

int pos_0_R = 0;
int pos_0_L = 0;
int stopped_toggle = 1;


#define SHOOT (pros::E_CONTROLLER_DIGITAL_A)


int aim_speed = 0;// p controller speed var
int aimVel = 0;

// Start op-control function
void opcontrol() {
  //autonomous();
  // Initialize variables for left joystick y-value and right joystick x-value
  float YL = 0;
  float XR = 0;
  float XL = 0;

  int cycle = 0;
  int lowerSpeed = 0;
  int shoot_on = 0;
  int aim_goal = 0;

  // Initialize variables for motor speeds
  int FL_speed = 0; // FL denotes front left motor
  int FR_speed = 0; // FR denotes front right motor
  int BL_speed = 0; // BL denotes back left motor
  int BR_speed = 0; // BR denotes back right motor

  // while loop used for maintaining opcontrol function
	while (true) {
    if (master.get_digital(AUTON)){
      autonomous();
    }
    // Construct instance of InvKinematics class to use motor driving functions
    // found in the InvKinematics class.
    InvKinematics Motor_Drive;

    // Halo Drive Mode (Left joystick controls forward and backwards, back
    // joystick controls turning)
    // Capture left joystick y-value and right joystick x-value
    YL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    XR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    XL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

    // Pass joystick values through a cubic function to provide smoother
    // driving operation
    YL = pow((YL/127),3) * 127;
    XL = pow((XL/127),3) * 127;
    //XR = pow((XR/127),3) * 127;

    // Compute speeds of each drive motor of the robot
    /*FL_speed = YL+XR;
    FR_speed = YL-XR;
    BL_speed = YL+XR;
    BR_speed = YL-XR;*/

    FL_speed = YL+XL;
    FR_speed = YL-XL;
    BL_speed = YL+XL;
    BR_speed = YL-XL;

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

    if(master.get_digital(INTAKE)){
      Motor_Drive.hold(Intake,INTAKE_SPEED * 0.67);
      stopped_toggle = 1;
    }
    else if(master.get_digital(OUTTAKE)){
      Motor_Drive.hold(Intake,OUTTAKE_SPEED * 0.67);
      stopped_toggle = 1;
    }
    else{
      if (stopped_toggle == 1){
        stopped_toggle == 0;
        pos_0_R = inRight.get_position();
        pos_0_L = inLeft.get_position();
        }
      inLeft.move_absolute(pos_0_L);
      inRight.move_absolute(pos_0_R);
    }


    encAIM = launchAngle.get_position();
    // Toggle launcher angle to upright position


    //Stops lowering the launcher at a certain point
    //if ((Low)<=(0)){
      //  launchAngle.move(0);
      //}
    // When held lower launcher angle
    if(master.get_digital(LOWER)){ //Need bottom constraint for Lower
      aim_goal = 0;
    }
    else if(master.get_digital(AIM)){ //Need toggle for AIM
      aim_goal = 1;
    }

    if(master.get_digital(MANUAL_LOWER)){
      launchAngle.move(-127);
      launchAngleLeft.move(-127);
    }

    if (aim_goal == 0){
      if (encAIM >= 40){
        aim_speed = -AIM_SPEED;
      }
      else{
        aim_speed = 0;
      }
    }

    else if (aim_goal == 1){
      if (encAIM >= 0){
        aimVel = launchAngle.get_actual_velocity();
        aim_speed = ((MOTOR_LAUNCHER_ANGLE_MAX-encAIM) + 20) - 1*aimVel;
      }
      else{
        aim_speed = AIM_SPEED;
      }
    }

    encSR = shootLeft.get_position();
    encSL = shootRight.get_position();
    // When pushed cycle through one launch of shooter
    if(master.get_digital(SHOOT)){
      shoot_on = 1;
      shoot_goal = SHOOT_MAX;
    }
    // When no launcher movement is needed motors are off
    if ((encSR < shoot_goal) && (shoot_on == 1)){
      shootLeft.move(127);
      shootRight.move(127);
    }
    else if((encSR >= shoot_goal) && (shoot_on == 1)){
      shootLeft.move(-127);
      shootRight.move(-127);
      shootLeft.tare_position();
      shootRight.tare_position();
      shootLeft.move(0);
      shootRight.move(0);
      shoot_on = 0;
    }

    launchAngle.move(aim_speed);
    launchAngleLeft.move(aim_speed);


// Grab Encoder values
      if(master.get_digital(DISP_ENCODERS)){
        encFR = frontRight.get_position();
        encFL = frontLeft.get_position();
        encBR = backRight.get_position();
        encBL = backLeft.get_position();
        encAIM = launchAngle.get_position();
        sprintf(str1, "FR = %d", encFR);
        sprintf(str2, "FL = %d", encFL);
        sprintf(str3, "BR = %d", encBR);
        sprintf(str4, "BL = %d", encBL);
        sprintf(str5, "AIM = %d", encAIM);
        pros::lcd::set_text(1, str1);
        pros::lcd::set_text(2, str2);
        pros::lcd::set_text(3, str3);
        pros::lcd::set_text(4, str4);
        pros::lcd::set_text(5, str5);
        pros::delay(20);
      }
      else if (master.get_digital(TARE_ENCODERS)){
        frontRight.tare_position();
        frontLeft.tare_position();
        backRight.tare_position();
        backLeft.tare_position();
        launchAngle.tare_position();
        pros::lcd::set_text(1, "FR = 0");
        pros::lcd::set_text(2, "FL = 0");
        pros::lcd::set_text(3, "BR = 0");
        pros::lcd::set_text(4, "BL = 0");
        pros::lcd::set_text(5, "AIM = 0");
        pros::delay(20);
      }

	}
}
