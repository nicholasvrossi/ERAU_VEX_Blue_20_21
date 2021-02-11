#include "motor_def.hpp"
#include "../../G_inc/source/InvKinematics.cpp"
#include "main.h"
#include "math.h"
#include <iostream>
using namespace std;

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
int n = 2;
int speed = 127;
int arr[n][5] = {
  {, , , ,},
  {, , , ,}
};

for(int[] row: arr){
  if row[4] == intake{

  }

  elseif row[4] == outtake


  moveTo(row[0],row[1],row[2],row[3],speed);
}

}
*/}

void moveTo(int FR,int FL,int BR,int BL,int speed){

  // FR
  frontRight.move_absolute(FR,speed)
  frontRight.move_absolute(FR,speed);

  // FL
  frontRight.move_absolute(FL,speed)
  frontRight.move_absolute(FL,speed);

  // BR
  backRight.move_absolute(BR,speed)
  backRight.move_absolute(BR,speed);

  // BL
  backLeft.move_absolute(BL,speed)
  backLeft.move_absolute(BL,speed);
 }
