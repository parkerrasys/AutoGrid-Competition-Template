/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftDrive            motor_group   5, 6            
// rightDrive           motor_group   4, 7            
// Inertial             inertial      8               
// ---- END VEXCODE CONFIGURED DEVICES ----

// Version 0.2.0-alpha
// Credits to Parker & Mia :)
//test

#include "vex.h"
#include "autogrid.h"

using namespace vex;

// A global instance of competition
competition Competition;
double wheelDiameter = 4;
double oneInch = (360)/(wheelDiameter*M_PI);
double oneTile = 24*oneInch;

float robotPosX;
float robotPosY;
float robotRotation = 0;
float robotSizeFB;
float robotSizeLR;

void leftDriveControl() {
  leftDrive.setVelocity(Controller1.Axis3.position(percent), percent);
  leftDrive.spin(forward);
}

void rightDriveControl() {
  rightDrive.setVelocity(Controller1.Axis2.position(percent), percent);
  rightDrive.spin(forward);
}

void pre_auton(void) {
  vexcodeInit();
  leftDrive.setStopping(brake);
  rightDrive.setStopping(brake);
  Inertial.calibrate();
  setStarting(2,0);
  setSize(18, 18);
}

void autonomous(void) {
    moveTo(2,1);
    moveTo(3,1);
    moveTo(4,2);
    moveTo(3,1);
    moveTo(2,1);
    moveTo(2,0);
    lookAt(2,1);
}

//For personal testing during teleop
void noLimitAuton() {
    moveTo(2,1);
    moveTo(3,1);
    moveTo(4,2);
    moveTo(3,1);
    moveTo(2,1);
    moveTo(2,0);
    lookAt(2,1);
}

void usercontrol(void) {
  Controller1.Axis3.changed(leftDriveControl);
  Controller1.Axis2.changed(rightDriveControl);
  Controller1.ButtonA.pressed(noLimitAuton);
  while (1) {

    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
