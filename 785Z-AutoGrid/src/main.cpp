/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Title:        AutoGrid Competition Template                             */
/*    Author:       785Z                                                      */
/*    Created:      Thu March 20 2025                                         */
/*    Description:  Official Compeition Template for AutoGrid                 */
/*    Last Update:  4/14/2025                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "autogrid.h"

using namespace vex;

// A global instance of competition
competition Competition;

void leftDriveControl() {
  leftDrive.setVelocity(Controller1.Axis3.position(percent), percent);
  leftDrive.spin(forward);
}

void rightDriveControl() {
  rightDrive.setVelocity(Controller1.Axis2.position(percent), percent);
  rightDrive.spin(forward);
}

// Pre_Auton Funtion
void pre_auton(void) {
  vexcodeInit();
  leftDrive.setStopping(brake);
  rightDrive.setStopping(brake);
  Inertial.calibrate();
  setSize(18, 18);
}

// Autonomous funtion
void autonomous(void) {
  setStarting(2, 1);
  moveTo(2, 2);
}

void usercontrol(void) {
  Controller1.Axis3.changed(leftDriveControl);
  Controller1.Axis2.changed(rightDriveControl);
  while (1) {
    wait(20, msec);
  }
}

int main() {
  // Setup Bot for Match
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();

  while (true) {
    wait(100, msec);
  }
}