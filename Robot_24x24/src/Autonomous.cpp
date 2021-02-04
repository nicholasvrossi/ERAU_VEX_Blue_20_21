#include "motor_def.hpp"
#include "main.h"
#include "math.h"
#include <iostream>
#include <vector>
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
enum commands {intake, outtake, eject};
const int n = 2;
int speed = 110;
int numCounts = 2000; // While Loop limit
// int arr[n][6] = {
//   // {, , , , ,},
//   // {, , , , ,}
// };
vector<int*> arr = {

};

for(int* row: arr){
  if (row[5] == intake){
    inLeft.move(INTAKE_SPEED);
    inRight.move(INTAKE_SPEED);
    liftRight.move(LIFT_UP_SPEED);
    liftLeft.move(LIFT_UP_SPEED);
    ejector.move(EJECTOR_EJECT);
  }
  else if (row[5] == outtake){
    inLeft.move(OUTTAKE_SPEED);
    inRight.move(OUTTAKE_SPEED);
    liftRight.move(LIFT_DN_SPEED);
    liftLeft.move(LIFT_DN_SPEED);
    ejector.move(-EJECTOR_EJECT);
  }
  else if (row[5] == eject){
    inLeft.move(0);
    inRight.move(0);
    liftRight.move(0);
    liftLeft.move(0);
    ejector.move(EJECTOR_EJECT);
  }
  else{
    inLeft.move(0);
    inRight.move(0);
    liftRight.move(0);
    liftLeft.move(0);
    ejector.move(0);
  }

  int speed = row[4];
  int ii = 0;
  int error0 = 0;
  int error1 = 0;
  int error2 = 0;
  int error3 = 0;


  frontRight.tare_position();
  frontLeft.tare_position();
  backRight.tare_position();
  backLeft.tare_position();

  while((ii <= numCounts) || (error0 < (error0 - 5) &  error1 < (error1 - 5) & error2 < (error2 - 5) & error3 < (error3 - 5))){
  moveTo(row[0],row[1],row[2],row[3],speed);
  ii++;
  }
  frontRight.move(0);
  frontLeft.move(0);
  backRight.move(0);
  backLeft.move(0);
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
