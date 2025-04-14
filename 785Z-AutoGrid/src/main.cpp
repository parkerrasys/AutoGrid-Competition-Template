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

// Version 0.2.3-alpha
// Credits to Parker Rasys & Mia Keegan :)

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
double wheelDiameter = 4;
double oneInch = (360)/(wheelDiameter*M_PI);
double oneTile = 24*oneInch;

int autonDriveSpeed = 50;

float robotPosX;
float robotPosY;
float robotRotation = 0;
float robotSizeFB;
float robotSizeLR;
double remainingDistance;
double speedFactor;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// AutoGrid Funtions - DO NOT REMOVE
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void setSize(float FB, float LR) {
  robotSizeFB = FB;
  robotSizeLR = LR;
}

void setStarting(float startingX, float startingY) {
  robotPosX = startingX;
  robotPosY = startingY;
}

void rotateBot(double theta) {
  Inertial.setRotation(0, degrees);
  double angleDiff = theta;
  double turningSpeed = Inertial.rotation(degrees) - angleDiff;
  while (angleDiff > 180 || angleDiff <= -180) {
    if (angleDiff > 180) {
      angleDiff -= 360;
    } else if (angleDiff <= -180) {
      angleDiff += 360;
    }
  }

  while (fabs(turningSpeed) >= 1.25) {
    turningSpeed = (Inertial.rotation(degrees) - angleDiff) / 1.25;
    leftDrive.spin(reverse, turningSpeed, percent);
    rightDrive.spin(forward, turningSpeed, percent);
  }

  leftDrive.stop();
  rightDrive.stop();
  robotRotation += Inertial.rotation(degrees);
  leftDrive.setPosition(0, degrees);
  rightDrive.setPosition(0, degrees);
}

double toDegrees(double radians) {
  double degrees = radians * 180.0 / M_PI;

  while (degrees > 180 || degrees < -180) {
    if (degrees > 180) {
      degrees -= 360;
    } else if (degrees <= -180) {
      degrees += 360;
    }
  }

  return degrees;
}

double findC(double a, double b)
{
  return(sqrt(pow(a,2)+pow(b,2)));
}

double findAngle(double a, double b)
{
  return(toDegrees(atan2(a,b)));
}

void moveTo(double valueX, double valueY) {
	double a = (valueX - robotPosX);
	double b = (valueY - robotPosY);
	double c = findC(a,b);
  double theta = findAngle(a,b);
  double driveDistance = c*oneTile;
	rotateBot(theta - robotRotation);
  leftDrive.setVelocity(autonDriveSpeed, percent);
  rightDrive.setVelocity(autonDriveSpeed, percent);
	leftDrive.spinFor(forward, driveDistance, degrees, false);
	rightDrive.spinFor(forward, driveDistance, degrees);
  robotPosX = valueX;
  robotPosY = valueY;
  leftDrive.setPosition(0, degrees);
  rightDrive.setPosition(0, degrees);
}

void reverseTo(double valueX, double valueY) {
	double a = (valueX - robotPosX);
	double b = (valueY - robotPosY);
	double c = findC(a,b);
  double theta = findAngle(a,b);
  double driveDistance = c*oneTile;
	rotateBot(theta - robotRotation - 180);
  leftDrive.setVelocity(autonDriveSpeed, percent);
  rightDrive.setVelocity(autonDriveSpeed, percent);
	leftDrive.spinFor(reverse, driveDistance, degrees, false);
	rightDrive.spinFor(reverse, driveDistance, degrees);
  robotPosX = valueX;
  robotPosY = valueY;
  leftDrive.setPosition(0, degrees);
  rightDrive.setPosition(0, degrees);
}


void lookAt(double valueX, double valueY) {
	double a = (valueX - robotPosX);
	double b = (valueY - robotPosY);
  double theta = findAngle(a,b);
	rotateBot(theta);
}
// -=-=-=-=-=-=-=-=-=-=-=-=-
// End of AutoGrid Funtions
// -=-=-=-=-=-=-=-=-=-=-=-=-

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

//For personal testing during teleop
void noLimitAuton() {
    moveTo(2,1);
    moveTo(2,0);
    lookAt(2,1);
    leftDrive.stop();
    rightDrive.stop();
}

// Function for calibrating
void calibrateInertial() {
  Inertial.calibrate();
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Calibrating...");
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("Battery: %3.2f%", Brain.Battery.capacity());
  while(Inertial.isCalibrating()) {
    wait(20, msec);
  }
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Ready!");
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("Battery: %3.2f%", Brain.Battery.capacity());
  Controller1.rumble(".");
}

void usercontrol(void) {
  Controller1.Axis3.changed(leftDriveControl);
  Controller1.Axis2.changed(rightDriveControl);
  Controller1.ButtonY.pressed(noLimitAuton);
  Controller1.ButtonB.pressed(calibrateInertial);
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