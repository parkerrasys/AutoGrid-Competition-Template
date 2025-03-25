#include "vex.h"

extern double wheelDiameter = 4;
extern double oneInch = (360)/(wheelDiameter*M_PI);
extern double oneTile = 24*oneInch;
extern float robotPosX;
extern float robotPosY;
extern float robotRotation = 0;
extern float robotSizeFB;
extern float robotSizeLR;

void setSize(float FB, float LR) {
  robotSizeFB = FB;
  robotSizeLR = LR;
}

void setStarting(int startingX, int startingY) {
  robotPosX = startingX;
  robotPosY = startingY;
}

void rotateBot(double theta) {
  double turningSpeed = Inertial.rotation(degrees) - theta;
  while(fabs(turningSpeed) >= 1.5){
    turningSpeed = (Inertial.rotation(degrees) - theta)/2;
    leftDrive.spin(reverse, turningSpeed, percent);
    rightDrive.spin(forward, turningSpeed, percent);
  }
  robotRotation += Inertial.rotation(degrees);
}

double toDegrees(double radians)
{
  return(radians*180/M_PI);
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
	rotateBot(theta);
  leftDrive.setVelocity(50, percent);
  rightDrive.setVelocity(50, percent);
	leftDrive.spinFor(forward, c*oneTile, degrees, false);
	rightDrive.spinFor(forward, c*oneTile, degrees);
  robotPosX = valueX;
  robotPosY = valueY;
}

void lookAt(double valueX, double valueY) {
	double a = (valueX - robotPosX);
	double b = (valueY - robotPosY);
  double theta = findAngle(a,b);
	rotateBot(theta);
}