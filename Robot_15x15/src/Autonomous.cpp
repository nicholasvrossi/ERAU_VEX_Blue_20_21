#include "motor_def.hpp"
#include "main.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define TURN90_L (-500)
#define TURN90_R (500)
#define TURNN90_L (500)
#define TURNN90_R (-500)

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
vector<int> waypoint(int fr, int fl, int br, int bl, float speed, int cmd) {
    vector<int> way = {fr, fl, br, bl, (int) speed, cmd};
    return way;
}

enum commands{intake, outtake, aim, lower, shoot} ;

void autonomous() {

//int n = 2;
//int speed = 127;
/*int arr[n][5] = {
  {, , , ,},
  {, , , ,}
};*/
//enum commands {intake, outtake, eject};
//const int n = 2;
int speed = 100;
int encAIM = 0;
int encAIM_goal = 0;
int enc_shootLeft = 0;
int pauseTime = 0;

int encFR = 0;
int encFL = 0;
int encBR = 0;
int encBL = 0;

int ii = 0;
int jj = 0;
int error0 = 0;
int error1 = 0;
int error2 = 0;
int error3 = 0;

int aimVel = 0;
int aim_speed = 0;
int deltaTime = 0;
int timestamp = 0;
int errorFR = 0;
int errorFL = 0;
int errorBR = 0;
int errorBL = 0;
int speedFR = 0;
int speedFL = 0;
int speedBR = 0;
int speedBL = 0;
int integralFR = 0;
int integralFL = 0;
int integralBR = 0;
int integralBL = 0;
int derivativeFR = 0;
int derivativeFL = 0;
int derivativeBR = 0;
int derivativeBL = 0;

double Kp = 127/1000;
double Ki = 0.000001;
double Kd = 3;
int integralActiveRange = 30;

int numCounts = 500000; // While Loop limit
// FR, FL, BR, BL, speed, command
void moveTo(int speedFR, int speedFL, int speedBR, int speedBL);

vector<vector<int> > arr = { // original
    /*waypoint(-365, -365, -365, -365, speed * .5, intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(0,0,0,0,speed,shoot),
    waypoint(0,0,0,0,speed,lower),
    waypoint(-580,580,-580,580,speed*.5,-1),
    waypoint(2900,2900,2900,2900,speed*.5,intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(425,-425,425,-425, speed*.5,-1),
    waypoint(-130,-130,-130,-130,speed*.5,-1),
    waypoint(0,0,0,0,speed,shoot),
    waypoint(0,0,0,0,speed,lower),
    /*waypoint(-965,965,-965,965,speed*.5,-1),
    waypoint(810,810,810,810,speed*.5,intake),
    waypoint(950,-950,950,-950,speed*.5,-1),
    waypoint(0,0,0,0,speed,aim),
    waypoint(750,750,750,750,speed*.5,-1),
    waypoint(0,0,0,0,speed,shoot),*/
    /*waypoint(-513,-513,-513,-513,speed*.5,-1),
    waypoint(-490,490,-490,490,speed*.5,-1),
    waypoint(3000,3000,3000,3000,speed*.5,intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(-1000,-1000,-1000,-1000,speed*.5,-1),
    waypoint(250,-250,250,-250,speed*.5,-1),
    waypoint(1000,1000,1000,1000,speed*.5,-1),
    waypoint(0,0,0,0,speed*.5,shoot),
    waypoint(-1000,-1000,-1000,-1000,speed*.5,lower),
    waypoint(270,-270,270,-270,speed*.5,-1),
    waypoint(1000,1000,1000,1000,speed*.5,intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(0,0,0,0,speed*.5,shoot),
    waypoint(0,0,0,0,speed,lower),
    waypoint(-1430,-1430,-1430,-1430,speed*.5,-1),
    waypoint(225,-225,225,-225,speed*.5,-1),
    waypoint(1500,1500,1500,1500,speed*.5,intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(-3150,-3150,-3150,-3150,speed*.5,-1),
    waypoint(-475,475,-475,475,speed*.5,-1),
    waypoint(550,550,550,550,speed*.5,-1),
    waypoint(0,0,0,0,speed,shoot),
    waypoint(0,0,0,0,speed,lower),
    waypoint(-525,525,-525, 525,speed*.5,-1),
    waypoint(3000,3000,3000,3000,speed*.5,intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(-570,-570,-570,-570,speed*.5,-1),
    waypoint(330,-330,330,-330,speed*.5,-1),
    waypoint(300,300,300,300,speed*.5,-1),
    waypoint(0,0,0,0,speed,shoot),
    waypoint(-300,-300,-300,-300,speed*.5,lower),
    waypoint(-700,700,-700,700,speed*.5,-1)*/
    waypoint(-500,500,-500,500,speed*0.3,-1)
  };

for(vector<int> row: arr){
  if (row[5] == intake){
    cout << "hi 1" << endl;
    inLeft.move(INTAKE_SPEED);
    inRight.move(INTAKE_SPEED);
    pauseTime = 3000;

  }
  else if (row[5] == outtake){
    cout << "hi 2" << endl;
    inLeft.move(OUTTAKE_SPEED);
    inRight.move(OUTTAKE_SPEED);
    pauseTime = 1000;

  }
  else if (row[5] == aim){
    cout << "hi 3" << endl;
    inLeft.move(0);
    inRight.move(0);
    encAIM_goal = 155;
    encAIM = launchAngle.get_position();
    while ((abs(encAIM) < abs(encAIM_goal)) ||(jj < 50000)){
      if (encAIM >= 0){
        aimVel = launchAngle.get_actual_velocity();
        aim_speed = ((MOTOR_LAUNCHER_ANGLE_MAX-encAIM) + 20) - 1*aimVel;
      }
      else{
        aim_speed = AIM_SPEED;
      }
      encAIM = launchAngle.get_position();
      launchAngle.move(aim_speed);
      launchAngleLeft.move(aim_speed);
      jj++;
    }
    launchAngle.move(30);
    launchAngleLeft.move(30);
    pauseTime = 3000;

  }
  else if(row[5] == lower){
    cout << "hi 4" << endl;
    inLeft.move(0);
    inRight.move(0);
    encAIM_goal = 0;
    encAIM = launchAngle.get_position();
    while (encAIM > 20){
      launchAngle.move(-45);
      launchAngleLeft.move(-45);
      encAIM = launchAngle.get_position();
    }
    launchAngle.move(0);
    launchAngleLeft.move(0);
    pauseTime = 3000;

  }
  else if(row[5] == shoot){
    cout << "hi 5" << endl;
    inLeft.move(0);
    inRight.move(0);
    enc_shootLeft = shootLeft.get_position();
    shootLeft.tare_position();
    while (enc_shootLeft < 2300){
      shootLeft.move(127);
      shootRight.move(127);
      enc_shootLeft = shootLeft.get_position();
    }
    shootLeft.move(0);
    shootRight.move(0);
    pauseTime = 3000;

  }
  else{
    cout << "hi 0" << endl;
    inLeft.move(0);
    inRight.move(0);
    pauseTime = 1000;
  }

  speed = row[4];
  ii = 0;

  // PID DRIVING SECTION
  frontRight.tare_position();
  frontLeft.tare_position();
  backRight.tare_position();
  backLeft.tare_position();

  errorFR = row[0] - encFR;
  errorFL = row[1] - encFL;
  errorBR = row[2] - encBR;
  errorBL = row[3] - encBL;

  timestamp = pros::millis();
  while((ii <= numCounts) && ((abs(errorFR) > 1) || (abs(errorFL) > 1) || (abs(errorBR) > 1) || (abs(errorBL) > 1))){
    ii++;
    cout << ii << endl;;
    encFR = frontRight.get_position()+errorFR;
    encFL = frontLeft.get_position()+errorFL;
    encBR = backRight.get_position()+errorBR;
    encBL = backLeft.get_position()+errorBL;

    errorFR = row[0] - encFR;
    errorFL = row[1] - encFL;
    errorBR = row[2] - encBR;
    errorBL = row[3] - encBL;

    deltaTime = pros::millis() - timestamp;
    timestamp = pros::millis();

    // integralFR
    if (errorFR == 0|| abs(errorFR) > integralActiveRange){
      integralFR = 0;}
    else{
      integralFR += (errorFR) * deltaTime;}
      // integralFL
    if (errorFL == 0|| abs(errorFL) > integralActiveRange){
      integralFL = 0;}
    else{
      integralFL += (errorFL) * deltaTime;}
        // integralBR
    if (errorBR == 0|| abs(errorBR) > integralActiveRange){
      integralBR = 0;}
    else{
      integralBR += (errorBR) * deltaTime;
    };
    // integralBL
    if (errorBL == 0|| abs(errorBL) > integralActiveRange){
      integralBL = 0;
    }
    else{
      integralBL += (errorBL) * deltaTime;
    };

    // derivativeFR
    derivativeFR = frontRight.get_actual_velocity();
    // derivativeFL
    derivativeFL = frontLeft.get_actual_velocity();
    // derivativeBR
    derivativeBR = backRight.get_actual_velocity();
    // derivativeBL
    derivativeBL = backLeft.get_actual_velocity();

    // set motor speed
    speedFR = Kp * errorFR +
              Ki * integralFR +
              Kd * derivativeFR;
    speedFL = Kp * errorFL +
              Ki * integralFL +
              Kd * derivativeFL;
    speedBR = Kp * errorBR +
              Ki * integralBR +
              Kd * derivativeBR;
    speedBL = Kp * errorBL +
              Ki * integralBL +
              Kd * derivativeBL;
    speedFR = clamp(speedFR, -127, 127);
    speedFL = clamp(speedFL, -127, 127);
    speedBR = clamp(speedBR, -127, 127);
    speedBL = clamp(speedBL, -127, 127);
    moveTo(speedFR,speedFL,speedBR,speedBL);
  }
  frontRight.move(0);
  frontLeft.move(0);
  backRight.move(0);
  backLeft.move(0);
  // pros::delay(pauseTime);
  if (row[5] == intake){
    inLeft.move(0);
    inRight.move(0);
  }
  pros::delay(1500);
}

}

/*void moveTo(int FR,int FL,int BR,int BL,int speed){

  // FR
  frontRight.move_absolute(FR,speed);

  // FL
  frontLeft.move_absolute(FL,speed);

  // BR
  backRight.move_absolute(BR,speed);

  // BL
  backLeft.move_absolute(BL,speed);
}*/



 vector<int> turn90(int speed, enum commands var){
   vector<int> way = waypoint(TURN90_R, TURN90_L, TURN90_R, TURN90_L, speed, var);
   return way;
 }

 vector<int> turnN90(int speed, enum commands var){
   vector<int> way = waypoint(TURNN90_R, TURNN90_L, TURNN90_R, TURNN90_L, speed, var);
   return way;
 }

 void moveTo(int speedFR, int speedFL, int speedBR, int speedBL){
   // FR
   frontRight.move(speedFR);

   // FL
   frontLeft.move(speedFL);

   // BR
   backRight.move(speedBR);

   // BL
   backLeft.move(speedBL);
 }
