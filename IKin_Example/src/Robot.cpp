#include <vector>
#include <cmath>
#include "main.h"
#include "Robot.hpp"
#include "RampingMotor.hpp"


//*********************************
// Drive train constant definitions
//*********************************
const int Robot::MOVE_FORWARD = 127;
const int Robot::MOVE_BACKWARD = -Robot::MOVE_FORWARD;
const int Robot::STRAFE_RIGHT = 127;
const int Robot::STRAFE_LEFT = -Robot::STRAFE_RIGHT;
const int Robot::ROTATE_CW = 127;
const int Robot::ROTATE_CCW = -Robot::ROTATE_CW;

//***********************************
// Tray actuator constant definitions
//***********************************
const int Robot::TRAY_RAISE = 127;
const int Robot::TRAY_LOWER = -Robot::TRAY_RAISE;
const int Robot::TRAY_RAISED = 100; // TODO make sure that the fully raised tray is this number
const int Robot::TRAY_LOWERED = 0;

//**************************
// Arm constant definitions
//**************************
const int Robot::ARM_RAISE = 50;
const int Robot::ARM_LOWER = -60;
const int Robot::ARM_RAISED = 30; // TODO make sure that the fully raised arm is this number
const int Robot::ARM_LOWERED = 0;


//****************************
// Intake constant definitions
//****************************
const int Robot::INTAKE_PULL = 127;
const int Robot::INTAKE_PUSH = -Robot::INTAKE_PULL;

//*******************
// Drive train motors
//*******************
pros::RampingMotor Robot::frontLeft  = pros::RampingMotor(MOTOR_FRONT_LEFT_PORT,
                                              pros::E_MOTOR_GEARSET_18,
                                              false,
                                              DRIVE_RAMP_SCALE);
pros::RampingMotor Robot::frontRight = pros::RampingMotor(MOTOR_FRONT_RIGHT_PORT,
                                              pros::E_MOTOR_GEARSET_18,
                                              true,
                                              DRIVE_RAMP_SCALE);
pros::RampingMotor Robot::backLeft   = pros::RampingMotor(MOTOR_BACK_LEFT_PORT,
                                              pros::E_MOTOR_GEARSET_18,
                                              false,
                                              DRIVE_RAMP_SCALE);
pros::RampingMotor Robot::backRight  = pros::RampingMotor(MOTOR_BACK_RIGHT_PORT,
                                              pros::E_MOTOR_GEARSET_18,
                                              true,
                                              DRIVE_RAMP_SCALE);

//*********************
// Tray actuator motors
//*********************
pros::RampingMotor Robot::actuator = pros::RampingMotor(MOTOR_TRAY_ACTUATOR_PORT,
                                            pros::E_MOTOR_GEARSET_36,
                                            false,
                                            DRIVE_RAMP_SCALE);

//**********
// Arm motor
//**********
pros::RampingMotor Robot::armRight = pros::RampingMotor(ARM_RIGHT_PORT,
                                            pros::E_MOTOR_GEARSET_18,
                                            true,
                                            DRIVE_RAMP_SCALE);
pros::RampingMotor Robot::armLeft  = pros::RampingMotor(ARM_LEFT_PORT,
                                            pros::E_MOTOR_GEARSET_18,
                                            false,
                                            DRIVE_RAMP_SCALE);

//*************
// Intake motor
//*************
pros::RampingMotor Robot::intakeLeft  = pros::RampingMotor(INTAKE_LEFT_PORT,
                                               pros::E_MOTOR_GEARSET_18,
                                               false,
                                               DRIVE_RAMP_SCALE);
pros::RampingMotor Robot::intakeRight = pros::RampingMotor(INTAKE_RIGHT_PORT,
                                               pros::E_MOTOR_GEARSET_18,
                                               true,
                                               DRIVE_RAMP_SCALE);


// returns the sign of the value
inline int sign(double value) {
    return (int) (value / std::abs(value));
}

//*********************************
// Drive train function definitions
//*********************************
void Robot::forward(int velocity) {
    if (abs(velocity) >= DRIVE_MINIMUM_VOLTAGE) {
        frontLeft.move(velocity);
        frontRight.move(velocity);
        backLeft.move(velocity);
        backRight.move(velocity);
    }
}
void Robot::strafe(int velocity) {
    if (abs(velocity) >= DRIVE_MINIMUM_VOLTAGE) {
        frontLeft.move(velocity);
        frontRight.move(-velocity);
        backLeft.move(-velocity);
        backRight.move(velocity);
    }
}
void Robot::rotate(int velocity) {
    if (abs(velocity) >= DRIVE_MINIMUM_VOLTAGE) {
        frontLeft.move(velocity);
        frontRight.move(-velocity);
        backLeft.move(velocity);
        backRight.move(-velocity);
    }
}
// <<<<<<< HEAD
// std::vector<float> analogValueDisp(int left_x, int left_y){
//     float r;
//     float newX;
//     float newY;
//     float theta1;
//     float theta1d;
//     float theta2;
//     float theta2d;
//     float moveVal_1;
//     float moveVal_2;
//
//     pros::Motor motor4 (4); // black
//     pros::Motor motor1 (1); // black
//     pros::Motor motor3 (3); // blue
//     pros::Motor motor2 (2); // blue
//
// 	float max = std::max(std::abs(left_x), std::abs(left_y));
//
// 	if(((left_y != 0) && (left_x != 0)) || (max !=0)){
// 		r = sqrt((left_x)*(left_x) + (left_y)*(left_y));
//
// 		float maxX = left_x / max;
// 		float maxY = left_y / max;
//
// 		newX = ((r * maxX)*(r * maxX)*(r * maxX)) / (127.0*127);
// 		newY = ((r * maxY)*(r * maxY)*(r * maxY)) / (127.0*127);
// 	}
// 	else if(left_x == 0 && left_y == 0){
// 		newX = 0;
// 		newY = 0;
// 	}
//
//     r = sqrt((newX)*(newX) + (newY)*(newY));
//
//     //1st quad
//     if((newX>0 && newY>0) || (newX == 0 && newY > 0) || (newY == 0 && newX > 0)){
// 		// black wheels
// 		moveVal_1 = r;
//
// 		// blue wheels
// 		theta2 = (30*(3.14/180)) - (atan(newY/newX));
// 		theta2d = (theta2*(180/3.14));
// 		if(theta2 > 0){
// 			moveVal_2 = -r*(sin(theta2)/(sin(30*(3.14/180))));
// 		}
// 		else{
// 			moveVal_2 = r*(sin(theta2)/sin(-60*(3.14/180)));
// 		}
// 		if(newY == 0){
// 			moveVal_1 = r;
// 			moveVal_2 = -r;
// 		}
// 		else if(newX == 0){
// 			moveVal_1 = r;
// 			moveVal_2 = r;
// 		}
//     }
// =======
inline void remapCircleToSquare(int &x, int &y) {
    static const float R = 127 * std::sqrt(2); // sqrt(127^2 * 127^2) = 127 * sqrt(2)
// >>>>>>> 6df7c9956bb4fba8e099582493468fe84db59348

    float r = std::sqrt(x*x + y*y);

    float max = std::max(x, y);

    float maxX = x / max * 127;
    float maxY = y / max * 127;

    float newX = r/R * maxX;
    float newY = r/R * maxY;

    x = newX;
    y = newY;
}
void Robot::drive(int forwardVal, int strafeVal, int rotateVal) {
// <<<<<<< HEAD
//     std::vector<float> motVals = analogValueDisp(strafeVal, forwardVal);
//     int FLSpeed =
//     frontLeft.move(motVals[0] + rotateVal);
//     frontRight.move(motVals[1] - rotateVal);
//     backLeft.move(motVals[2] + rotateVal);
//     backRight.move(motVals[3] - rotateVal);
// =======
     // remapCircleToSquare(forwardVal, strafeVal);

     int fl = forwardVal + strafeVal + rotateVal,
         fr = forwardVal - strafeVal - rotateVal,
         bl = forwardVal - strafeVal + rotateVal,
         br = forwardVal + strafeVal - rotateVal;

     frontLeft.move(fl);
     frontRight.move(fr);
     backLeft.move(bl);
     backRight.move(br);
//>>> 6df7c9956bb4fba8e099582493468fe84db59348
}

//****************************************
// Autonomous control function definitions
//****************************************
void Robot::forwardDistance(double inches) {
    double target = inches * ENCODER_COUNTS_PER_INCH;
    int velocity = sign(inches) * Robot::MOVE_FORWARD;

    forward(velocity);

    while (std::abs(getDriveEncoderValue() - target) < ENCODER_TARGET_RANGE)
        pros::delay(1);

    forward(-velocity);
    pros::delay(getDriveVelocity() * DRIVE_VELOCITY_TO_BRAKE_TIME_MS);
    forward(0);
}
void Robot::strafeDistance(double inches) {
    double target = inches * ENCODER_COUNTS_PER_INCH;
    int velocity = sign(inches) * Robot::MOVE_FORWARD;

    strafe(velocity);

    while (std::abs(getDriveEncoderValue() - target) < ENCODER_TARGET_RANGE)
        pros::delay(1);

    strafe(-velocity);
    pros::delay(getDriveVelocity() * DRIVE_VELOCITY_TO_BRAKE_TIME_MS);
    strafe(0);
}
void Robot::rotateDegrees(double degrees) {
    double target = degrees * ENCODER_COUNTS_PER_DEGREE;
    int velocity = sign(degrees) * Robot::MOVE_FORWARD;

    rotate(velocity);

    while (std::abs(getDriveEncoderValue() - target) < ENCODER_TARGET_RANGE)
        pros::delay(1);

    rotate(-velocity);
    pros::delay(getDriveVelocity() * DRIVE_VELOCITY_TO_BRAKE_TIME_MS);
    rotate(0);
}

//**********************************
// Drive sensor function definitions
//**********************************
double Robot::getDriveEncoderValue() {
    double averageMagnitude =
            (std::abs(frontLeft.get_position())
           + std::abs(frontRight.get_position())
           + std::abs(backLeft.get_position())
           + std::abs(backRight.get_position())) / 4;

    int signProduct =
            sign(frontLeft.get_position())
          * sign(frontRight.get_position())
          * sign(backLeft.get_position())
          * sign(backRight.get_position());

    return signProduct * averageMagnitude;
}
double Robot::getDriveVelocity() {
    double averageMagnitude =
            (std::abs(frontLeft.get_actual_velocity())
           + std::abs(frontRight.get_actual_velocity())
           + std::abs(backLeft.get_actual_velocity())
           + std::abs(backRight.get_actual_velocity())) / 4;

    int signProduct =
            sign(frontLeft.get_actual_velocity())
          * sign(frontRight.get_actual_velocity())
          * sign(backLeft.get_actual_velocity())
          * sign(backRight.get_actual_velocity());

    return signProduct * averageMagnitude;
}

//***********************************
// Tray actuator function definitions
//***********************************
void Robot::actuateTray(int velocity) {
    actuator.move(velocity);
}

int Robot::getTrayPosition() {
    //actuator.get_positon();
    return 0;
}

//**************************
// Arm function definitions
//**************************
void Robot::armVelocity(int velocity) {
    armRight.move(velocity);
    armLeft.move(velocity);
}

//****************************
// Intake function definitions
//****************************
void Robot::intakeVelocity(int velocity) {
    intakeLeft.move(velocity);
    intakeRight.move(velocity);
}
