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
int error0 = 0;
int error1 = 0;
int error2 = 0;
int error3 = 0;


int numCounts = 500000; // While Loop limit
vector<vector<int> > arr = {
    {1000,1000 ,1000, 1000,speed ,-1},
    {-1100,-1100 ,-1100 ,-1100 ,speed ,-1},
    {0,0 ,0 ,0 ,speed ,intake},
    {0,0 ,0 ,0 ,speed ,outtake},
    {0,0 ,0 ,0 ,speed ,aim},
    {0,0 ,0 ,0 ,speed ,lower},
    {0,0 ,0 ,0 ,speed ,shoot}
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
    encAIM_goal = 177;
    encAIM = launchAngle.get_position();
    while (abs(encAIM) < abs(encAIM_goal)){
      launchAngle.move(50);
      encAIM = launchAngle.get_position();
    }
    launchAngle.move(20);
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
      encAIM = launchAngle.get_position();
    }
    launchAngle.move(0);
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
