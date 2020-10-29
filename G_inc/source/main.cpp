#include "main.h"
#include "InvKinematics.hpp"
#include "AbstractMovement.hpp"
#include "GaussianMovement.hpp"
#include "PIDMovement.hpp"
#include "BasicMovement.hpp"
#include "Robot.hpp"

#define RED_AUTON (1)



void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void invKinRecode() {
    InvKinematics kin;

    pros::MotorSet intakeMotors {
        Robot::intakeLeft,
        Robot::intakeRight
    };
    pros::MotorSet driveMotors {
        Robot::frontLeft,
        Robot::frontRight,
        Robot::backLeft,
        Robot::backRight
    };
    PIDConstants driveConsts;
    driveConsts.Kp = 0.02;
    driveConsts.Ki = 0.0000000005;
    driveConsts.Kd = 0.0003;
    driveConsts.integralActiveRange = 10;

    GaussianConstants actuatorConsts;
    actuatorConsts.n = 1;


    // expand robot
    kin.tare(Robot::actuator)->
        hold(intakeMotors, Robot::INTAKE_PUSH)->
        move(GaussianMovement().setConsts(actuatorConsts)->
            set(Robot::actuator, 3000)
        )->
        move(GaussianMovement().setConsts(actuatorConsts)->
            set(Robot::actuator, 200)
        )->
        delay(500)->
        stop(Robot::actuator)->
        delay(1000)->
        hold(intakeMotors, Robot::INTAKE_PULL);

    // Autonomous routine
    kin.tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, 3000)
        )->
        delay(1000)->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, -2000)
        )->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, 3000)
        )->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->setReversedIf(RED_AUTON)->
            set(Robot::frontLeft,   987)->
            set(Robot::frontRight, -1041)->
            set(Robot::backLeft,    1372)->
            set(Robot::backRight,  -1398)
        )->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, 2000)
        )->
        delay(1000)->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(Robot::frontLeft,  -480)->
            set(Robot::frontRight, -480)->
            set(Robot::backLeft,   -480)->
            set(Robot::backRight,  -500)
        )->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->setReversedIf(RED_AUTON)->
            set(Robot::frontLeft,  -1000)->
            set(Robot::frontRight,  1238)->
            set(Robot::backLeft,   -1028)->
            set(Robot::backRight,   1251)
        )->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, 1700)
        )->
        delay(2000)->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, 600)
        )->
        delay(1000)->
        stop(intakeMotors)->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->setReversedIf(RED_AUTON)->
            set(Robot::frontLeft,  -2186)->
            set(Robot::frontRight,  2127)->
            set(Robot::backLeft,   -1363)->
            set(Robot::backRight,   1390)
        )->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, 4000)
        )->
        delay(3000)->
        move(GaussianMovement().setConsts(actuatorConsts)->
            set(Robot::actuator, 3000)
        )->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(driveMotors, 100)
        )->
        delay(1000)->
        tare(driveMotors)->
        move(PIDMovement().setConsts(driveConsts)->
            set(Robot::frontLeft,  -480)->
            set(Robot::frontRight, -480)->
            set(Robot::backLeft,   -480)->
            set(Robot::backRight,  -500)
        );
}
void autonomous() {
    std::cout<<"autonomous"<<std::endl;
    /***********************************************************\
    | motor definitions - there are usually declared externally |
    \***********************************************************/
    pros::Motor driveFL(1);
    pros::Motor driveFR(3);
    pros::Motor driveBL(2);
    pros::Motor driveBR(4);
    pros::Motor armR(5);
    pros::Motor armL(6);
    pros::Motor claw(7);


    /**********************************\
    | kinematics controller definition |
    \**********************************/
    InvKinematics kin;


    /********************************************************************\
    | drive motor sets - these are collections of motors for convenience |
    \********************************************************************/
    pros::MotorSet driveMotors {
            driveFL,
            driveFR,
            driveBL,
            driveBR
    };
    // drive right side motor set - for convenience
    pros::MotorSet driveMotorsRight {
            driveFR,
            driveBR
    };
    // drive left side motor set - for convenience
    pros::MotorSet driveMotorsLeft {
            driveFL,
            driveBL
    };

    /***************************************************************\
    | drive motor constants - only set up for gaussian control here |
    \***************************************************************/
    GaussianConstants driveConsts;
    driveConsts.n = 10;
    driveConsts.stretch = 1800;
    driveConsts.minimum = 15;


    /***************\
    | arm motor set |
    \***************/
    pros::MotorSet armMotors {
        armR,
        armL
    };

    /*************************************************************\
    | arm motor constants - only set up for gaussian control here |
    \*************************************************************/
    GaussianConstants armConsts;
    armConsts.minimum = 5;


    //**************************************************************************
    // PHASE 1: get the object on the pedestal *********************************
    //**************************************************************************

        // start by moving forward a little
    kin.tare(driveMotors)->
        move(GaussianMovement().setConsts(driveConsts)->
            set(driveMotors, 1000)
        )->
        delay(300)->
        // turn to face pedestal
        tare(driveMotors)->
        move(GaussianMovement().setConsts(driveConsts)->setReversedIf(RED_AUTON)->
            set(driveMotorsRight,  500)->
            set(driveMotorsLeft,  -500)
        )->
        delay(300)->
        // open claw
        move(GaussianMovement().
            set(claw, 400)
        )->
        // raise arm to pedestal height
        move(GaussianMovement().setConsts(armConsts)->
            set(armMotors, 800)
        )->
        delay(300)->
        // drive up to the pedestal
        tare(driveMotors)->
        move(GaussianMovement().setConsts(driveConsts)->
            set(driveMotors, 2500)
        )->
        delay(300)->
        // grab the object on the pedestal
        hold(claw, -40)->
        delay(500)->
        // move back with the object in the claw
        tare(driveMotors)->
        move(GaussianMovement().setConsts(driveConsts)->
            set(driveMotors, 800)
        )->
        delay(300);

    //**************************************************************************
    // PHASE 2: score the object ***********************************************
    //**************************************************************************

        // face the scoring zone
    kin.tare(driveMotors)->
        move(GaussianMovement().setConsts(driveConsts)->setReversedIf(RED_AUTON)->
            set(driveMotorsRight, -800)->
            set(driveMotorsLeft,   300)
        )->
        delay(300)->
        // move the arm to the scoring zone height
        move(GaussianMovement().setConsts(armConsts)->
            set(armMotors, 300)
        )->
        delay(300)->
        // drive forward to the scoring zone
        tare(driveMotors)->
        move(GaussianMovement().setConsts(driveConsts)->
            set(driveMotors, 3500)
        )->
        delay(300)->
        // release the object in the claw
        pulse(claw, 40, 300)->
        // reverse so that the robot does not touch the object
        tare(driveMotors)->
        move(GaussianMovement().setConsts(driveConsts)->
            set(driveMotors, -500)
        );
}

void opcontrol() {
    /***********************************************************\
    | motor definitions - there are usually declared externally |
    \***********************************************************/
    pros::Motor driveFL(1);
    pros::Motor driveBL(2);
    pros::Motor driveFR(
            3,
            pros::E_MOTOR_GEARSET_18,
            true
    );
    pros::Motor driveBR(
            4,
            pros::E_MOTOR_GEARSET_18,
            true);
    pros::Motor armR(5);
    pros::Motor armL(6);
    pros::Motor claw(7);


    /**********************************\
    | kinematics controller definition |
    \**********************************/
    InvKinematics kin;


    /********************************************************************\
    | drive motor sets - these are collections of motors for convenience |
    \********************************************************************/
    pros::MotorSet driveMotors {
            driveFL,
            driveFR,
            driveBL,
            driveBR
    };
    // drive right side motor set - for convenience
    pros::MotorSet driveMotorsRight {
            driveFR,
            driveBR
    };
    // drive left side motor set - for convenience
    pros::MotorSet driveMotorsLeft {
            driveFL,
            driveBL
    };

    /***************************************************************\
    | drive motor constants - only set up for gaussian control here |
    \***************************************************************/
    // GaussianConstants driveConsts;
    // driveConsts.minimum = 15;
    BasicConstants driveConsts;
    driveConsts.timeConst = 0.25;


    /***************\
    | arm motor set |
    \***************/
    pros::MotorSet armMotors {
        armR,
        armL
    };

    /*************************************************************\
    | arm motor constants - only set up for gaussian control here |
    \*************************************************************/
    GaussianConstants armConsts;
    armConsts.minimum = 5;


    kin.tare(driveMotors)->
        move(BasicMovement().setConsts(driveConsts)->
            set(driveMotors, 1000)
        );
}
