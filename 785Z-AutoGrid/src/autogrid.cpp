#include "autogrid.h"
#include "vex.h"

namespace autogrid {

robot::robot(double wheelDiam, double gear)
  : wheelDiameter(wheelDiam), gearRatio(gear), 
    robotSizeFB(0), robotSizeLR(0), 
    robotRotation(0), robotPosX(0), robotPosY(0),
    autonDriveSpeed(50) {
  oneInch = (360) / (wheelDiameter * M_PI);
  oneTile = 24 * oneInch;
}

robot::~robot() {
}

void robot::setGearRatio(double inputGear, double outputGear) {
  gearRatio = (inputGear / outputGear);
  // reciprocalRatio = (outputGear/inputGear);
  // correctGear = 1 - reciprocalRatio;
}

void robot::setSize(double FB, double LR) {
  robotSizeFB = FB;
  robotSizeLR = LR;
}

void robot::setStarting(double startingX, double startingY) {
  robotPosX = startingX;
  robotPosY = startingY;
}

void robot::rotateBot(double theta) {
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

double robot::toDegrees(double radians) {
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

double robot::findC(double a, double b) {
  return(sqrt(pow(a, 2) + pow(b, 2)));
}

double robot::findAngle(double a, double b) {
  return(toDegrees(atan2(a, b)));
}

void robot::moveTo(double valueX, double valueY) {
  double a = (valueX - robotPosX);
  double b = (valueY - robotPosY);
  double c = findC(a, b);
  double theta = findAngle(a, b);
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

void robot::reverseTo(double valueX, double valueY) {
  double a = (valueX - robotPosX);
  double b = (valueY - robotPosY);
  double c = findC(a, b);
  double theta = findAngle(a, b);
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

void robot::lookAt(double valueX, double valueY) {
  double a = (valueX - robotPosX);
  double b = (valueY - robotPosY);
  double theta = findAngle(a, b);
  rotateBot(theta);
}

robot newRobot(double wheelDiameter, double gearRatio) {
  return robot(wheelDiameter, gearRatio);
}

// Auton paths implementations
void red1() {
  robot bot = newRobot(4, 1.0);
  bot.setStarting(0, 0);
  bot.moveTo(5, 0);
  bot.lookAt(5, 1);
}

void red2() {
  robot bot = newRobot(4, 1.0);
  bot.setStarting(0, 0);
  bot.moveTo(0, 1);
}

void red3() {
  robot bot = newRobot(4, 1.0);
  bot.setStarting(0, 0);
  bot.lookAt(1, -1);
}

void blue1() {
  robot bot = newRobot(4, 1.0);
  bot.setStarting(0, -1);
  bot.lookAt(2, 4);
}

void blue2() {
  robot bot = newRobot(4, 1.0);
  bot.setStarting(-1, -1);
  bot.lookAt(4, 3);
}

void blue3() {
  robot bot = newRobot(4, 1.0);
  bot.setStarting(0, 0);
  bot.moveTo(0, 1);
}

} // namespace autogrid