#ifndef AUTOGRID_H
#define AUTOGRID_H
#include "vex.h"

namespace autogrid {

class robot {
private:
  double robotSizeFB;
  double robotSizeLR;
  double robotRotation;
  double robotPosX;
  double robotPosY;
  double gearRatio;
  double remainingDistance;
  double speedFactor;
  double wheelDiameter;
  double oneInch;
  double oneTile;
  double reciprocalRatio;
  double correctGear;
  int autonDriveSpeed;

public:
  robot(double wheelDiam, double gear);
  ~robot();
  void setSize(double FB, double LR);
  void setStarting(double startingX, double startingY);
  void rotateBot(double theta);
  double toDegrees(double radians);
  double findC(double a, double b);
  double findAngle(double a, double b);
  void moveTo(double valueX, double valueY);
  void reverseTo(double valueX, double valueY);
  void lookAt(double valueX, double valueY);
  void setGearRatio(double inputGear, double outputGear);
};

robot newRobot(double wheelDiameter, double gearRatio);

void red1();
void red2();
void red3();
void blue1();
void blue2();
void blue3();

} // namespace autogrid
#endif // AUTOGRID_H