// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftDrive            motor_group   5, 6            
// rightDrive           motor_group   4, 7            
// Inertial             inertial      8               
// ---- END VEXCODE CONFIGURED DEVICES ----

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
#include "auto-selector.h"

using namespace autogrid;
using namespace vex;

// A global instance of competition
competition Competition;

robot myRobot = newRobot(4, 1);

int testrotate = 0;

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
  initAutoSelector();
  leftDrive.setStopping(hold);
  rightDrive.setStopping(hold);
  Inertial.calibrate();
  myRobot.setGearRatio(48, 36);
}

// Autonomous funtion
void autonomous(void) {
  runSelectedAutonomous();
}

void test() {
  runSelectedAutonomous();
}

void testLook() {
  myRobot.lookAt(1,0);
  myRobot.lookAt(0,-1);
  myRobot.lookAt(-1,0);
  myRobot.lookAt(0,0);
}

void usercontrol(void) {
  Controller1.ButtonX.pressed(test);
  Controller1.ButtonB.pressed(testLook);
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