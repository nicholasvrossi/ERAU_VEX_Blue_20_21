#include "main.h"
#include "../../G_inc/headers/InvKinematics.hpp"
#include "../../G_inc/headers/BasicMovement.hpp"
#include "../../G_inc/headers/GaussianMovement.hpp"
#include "../../G_inc/headers/AbstractMovement.hpp"
#include <cmath>// OpControl.cpp 15x15 robot
#include "motor_def.hpp"


// Define button to be pressed that slows robot's speed
#define SLOW_BUTTON (pros::E_CONTROLLER_DIGITAL_L2)
// Define button to be pressed that starts intake collection of balls
#define INTAKE (pros::E_CONTROLLER_DIGITAL_R1)
// Define button to be pressed that starts outtake dispose of balls
#define OUTTAKE (pros::E_CONTROLLER_DIGITAL_R2)


// motors you want to track
// NOTE: array is an array of pointers: must use 'new' keyword or dereferernce
//  and existing non-pointer motor
std::vector<pros::Motor> motors = {
    pros::Motor(1), // front left
    pros::Motor(2), // front right
    pros::Motor(3), // back left
    pros::Motor(4),
    pros::Motor(9),
    pros::Motor(6),
    pros::Motor(5)
      // back right
};

pros::Controller controllerMaster(pros::E_CONTROLLER_MASTER);


void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void driveControl() {

    // Initialize variables for left joystick y-value and right joystick x-value
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

        // Halo Drive Mode (Left joystick controls forward and backwards, back
        // joystick controls turning)
        // Capture left joystick y-value and right joystick x-value
        YL = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        XR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // Pass joystick values through a cubic function to provide smoother
        // driving operation
        YL = pow((YL/127),3) * 127;
        XR = pow((XR/127),3) * 127;

        // Compute speeds of each drive motor of the robot
        FL_speed = YL+XR;
        FR_speed = YL-XR;
        BL_speed = YL+XR;
        BR_speed = YL-XR;

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
        }
        else if(master.get_digital(OUTTAKE)){
            Motor_Drive.hold(Intake,OUTTAKE_SPEED * 0.67);
        }
        else{
            Motor_Drive.hold(inLeft,0);
            Motor_Drive.hold(inRight,0);
        }
	}
}
void opcontrol() {
    std::vector<int> storedVals;
    initialize();
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
