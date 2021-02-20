#include "motor_def.hpp"
#include "main.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void moveTo(int FR,int FL,int BR,int BL,int speed);

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
void autonomous() {
enum commands {intake, outtake, aim, lower, shoot};
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


int numCounts = 500000; // While Loop limit
// FR, FL, BR, BL, speed, command
vector<vector<int> > arr = {
    waypoint(-365, -365, -365, -365, speed * .5, intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(0,0,0,0,speed,shoot),
    waypoint(0,0,0,0,speed,lower),
    waypoint(-582,582,-582,582,speed*.5,-1),
    waypoint(2900,2900,2900,2900,speed*.5,intake),
    waypoint(0,0,0,0,speed,aim),
    waypoint(425,-425,425,-425, speed*.5,-1),
    waypoint(-130,-130,-130,-130,speed*.5,-1),
    waypoint(0,0,0,0,speed,shoot),
    waypoint(0,0,0,0,speed,lower),
    waypoint(965,-965,965,-965,speed*.5,-1),
    waypoint(810,810,810,810,speed*.5,intake),
    waypoint(950,-950,950,-950,speed*.5,-1),
    waypoint(0,0,0,0,speed,aim),
    waypoint(750,750,750,750,speed*.5,-1),
    waypoint(0,0,0,0,speed,shoot)
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
      launchAngle.move(-10);
      launchAngleLeft.move(-10);
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
    while (enc_shootLeft < 4100){
      shootLeft.move(127);
      shootRight.move(127);
      enc_shootLeft = shootLeft.get_position();
    }
    shootLeft.tare_position();
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

  frontRight.tare_position();
  frontLeft.tare_position();
  backRight.tare_position();
  backLeft.tare_position();

  encFR = frontRight.get_position();
  encFL = frontLeft.get_position();
  encBR = backRight.get_position();
  encBL = backLeft.get_position();

  cout << "hello!" << endl;
  moveTo(row[0],row[1],row[2],row[3],speed);

  while((ii <= numCounts) && ((abs(encFR) < (abs(row[0]) - 20)) && (abs(encFL) < (abs(row[1]) - 20)))){
    ii++;
    cout << ii << endl;;
    encFR = frontRight.get_position();
    encFL = frontLeft.get_position();
    encBR = backRight.get_position();
    encBL = backLeft.get_position();
  }
  frontRight.move(0);
  frontLeft.move(0);
  backRight.move(0);
  backLeft.move(0);
  // pros::delay(pauseTime);
  pros::delay(3000);
  if (row[5] == intake){
    inLeft.move(0);
    inRight.move(0);
    pros::delay(500);
  }
}

}

void moveTo(int FR,int FL,int BR,int BL,int speed){

  // FR
  frontRight.move_absolute(FR,speed);

  // FL
  frontLeft.move_absolute(FL,speed);

  // BR
  backRight.move_absolute(BR,speed);

  // BL
  backLeft.move_absolute(BL,speed);
 }
