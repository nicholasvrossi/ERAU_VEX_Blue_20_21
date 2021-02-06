#include "main.h"
#include "../../G_inc/source/InvKinematics.cpp"
#include "../../G_inc/source/BasicMovement.cpp"
#include "../../G_inc/source/GaussianMovement.cpp"
#include "../../G_inc/source/AbstractMovement.cpp"
#include <cmath>
#include "../include/motor_def.hpp"


// Define button to be pressed that slows robot's speed
#define SLOW_BUTTON (pros::E_CONTROLLER_DIGITAL_L2)
// Define button to be pressed that starts intake collection of balls
#define INTAKE (pros::E_CONTROLLER_DIGITAL_R1)
// Define button to be pressed that starts outtake dispose of balls
#define OUTTAKE (pros::E_CONTROLLER_DIGITAL_R2)

#define LIFT_UP_BTN (pros::E_CONTROLLER_DIGITAL_R1)
#define LIFT_DN_BTN (pros::E_CONTROLLER_DIGITAL_L1)
#define LIFT_AND_EJECT_BTN (pros::E_CONTROLLER_DIGITAL_A)


// motors you want to track
// NOTE: array is an array of pointers: must use 'new' keyword or dereferernce
//  and existing non-pointer motor
std::vector<pros::Motor> motors = {
    pros::Motor(1), // front left
    pros::Motor(2), // front right
    pros::Motor(3), // back left
    pros::Motor(4)  // back right
};

pros::Controller controllerMaster(pros::E_CONTROLLER_MASTER);


void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void driveControl() {
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
          // Motor_Drive.hold(inLeft,INTAKE_SPEED * 0.67);
          // Motor_Drive.hold(inRight,INTAKE_SPEED * 0.67);
          Motor_Drive.hold(Intake,INTAKE_SPEED * 0.67);
        }
        else if(master.get_digital(OUTTAKE)){
          // Motor_Drive.hold(inLeft,OUTTAKE_SPEED * 0.67);
          // Motor_Drive.hold(inRight,OUTTAKE_SPEED * 0.67);
          Motor_Drive.hold(Intake,OUTTAKE_SPEED * 0.67);
        }
        else{
          Motor_Drive.hold(inLeft,0);
          Motor_Drive.hold(inRight,0);
        }


        ballColor = colorSensor.get_value();

        if (master.get_digital(LIFT_AND_EJECT_BTN)) {
              Motor_Drive.hold(LiftSet, LIFT_UP_SPEED);
              Motor_Drive.hold(ejector, EJECTOR_EJECT);
        }
        if (master.get_digital(LIFT_UP_BTN)) {
            Motor_Drive.hold(LiftSet, LIFT_UP_SPEED);

            // reverse the ejector if color sensed is bad color
            if ((IS_RED && (BLUE_COLOR_MIN <= ballColor && ballColor <= BLUE_COLOR_MAX))
                    || (!IS_RED && (RED_COLOR_MIN <= ballColor && ballColor <= RED_COLOR_MAX))) {
                Motor_Drive.hold(ejector, EJECTOR_EJECT);
            }
            else{
                Motor_Drive.hold(ejector, LIFT_UP_SPEED);
            }

        }
        else if (master.get_digital(LIFT_DN_BTN)) {
            Motor_Drive.hold(LiftSet, LIFT_DN_SPEED);
            Motor_Drive.hold(ejector, LIFT_DN_SPEED);
        }
        else {
            Motor_Drive.hold(LiftSet, 0);
            Motor_Drive.hold(ejector, 0);
        }
    }
}
void opcontrol() {
    std::vector<int> storedVals;

    while (true) {
        for (int i = 0; i < motors.size(); ++i) {
            pros::Motor motor = motors[i];
            int encoderVal = motor.get_position();

            char encoderValStr[32];
            sprintf(encoderValStr, "%-2d: %d", i, encoderVal);

            pros::lcd::set_text(i, encoderValStr);

            while (controllerMaster.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
                storedVals.push_back(encoderVal);
                motor.tare_position();

                while (controllerMaster.get_digital(pros::E_CONTROLLER_DIGITAL_A))
                    pros::delay(50);
            }
            ++i;
        }

        while (controllerMaster.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            int index = 0;
            while (index < storedVals.size()) {
                std::cout << '{';

                for (int i = 0; i < motors.size(); ++i) {
                    if (i != 0)
                        std::cout << ", ";

                    std::cout << storedVals[index];
                }

                std::cout << "}," << std::endl;
            }

            while (controllerMaster.get_digital(pros::E_CONTROLLER_DIGITAL_B))
                pros::delay(50);
        }

        driveControl();
    }
}
