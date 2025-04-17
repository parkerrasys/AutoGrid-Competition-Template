#include "vex.h"
#include "autogrid.h"

// Your auton paths, these are not required. But you can use them for the auton selector.
void red1() {
  setStarting(0, 0);
  moveTo(5, 0);
  lookAt(5,1);
  // moveTo(2.5, 2.5);
  // moveTo(5, 0);
  // moveTo(0, 0);
  // lookAt(0, 1);
  // moveTo(0, 0);
}

void red2() {
  setStarting(0, 0);
  moveTo(0, 1);
}

void red3() {
  setStarting(0, 0);
  lookAt(1, -1);
}

void blue1() {
  setStarting(0, -1);
  lookAt(2, 4);
}

void blue2() {
  setStarting(-1, -1);
  lookAt(4, 3);
}

void blue3() {
  setStarting(0, 0);
  moveTo(0,1);
}

// Size Variables
double robotSizeFB = 0;
double robotSizeLR = 0;

// Robot Starting Configuration
double robotRotation = 0;
double robotPosX = 0;
double robotPosY = 0;

// Gear Ratio
double gearRatio = 1.0;

// Movment Factors
double remainingDistance = 0;
double speedFactor = 0;
double wheelDiameter = 4;
double oneInch = (360)/(wheelDiameter*M_PI);
double oneTile = 24*oneInch;
double reciprocalRatio;
double correctGear;
int autonDriveSpeed = 50;

// AutoGrid Functions
void setGearRatio(double inputGear, double outputGear) {
  gearRatio = (inputGear / outputGear);
  // reciprocalRatio = (outputGear/inputGear);
  // correctGear = 1 - reciprocalRatio;

}

void setSize(double FB, double LR) {
  robotSizeFB = FB;
  robotSizeLR = LR;
}

void setStarting(double startingX, double startingY) {
  robotPosX = startingX;
  robotPosY = startingY;
}

void rotateBot(double theta) {
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
  Inertial.setRotation(0, degrees);
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

double findC(double a, double b) {
  return(sqrt(pow(a,2)+pow(b,2)));
}

double findAngle(double a, double b) {
  return(toDegrees(atan2(a,b)));
}

void moveTo(double valueX, double valueY) {
  double a = (valueX - robotPosX);
  double b = (valueY - robotPosY);
  double c = findC(a,b);
  double theta = findAngle(a,b);
  // double driveDistance = c * oneTile*gearRatio - (correctGear * c);
  double driveDistance = c * oneTile / gearRatio;
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
  // double driveDistance = c * oneTile*gearRatio - (correctGear * c);
  double driveDistance = c * oneTile / gearRatio;
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