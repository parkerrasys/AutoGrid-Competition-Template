// Function declarations for AutoGrid
void setSize(double FB, double LR);
void setStarting(double startingX, double startingY);
void rotateBot(double theta);
double toDegrees(double radians);
double findC(double a, double b);
double findAngle(double a, double b);
void moveTo(double valueX, double valueY);
void reverseTo(double valueX, double valueY);
void lookAt(double valueX, double valueY);

// External variable declarations
extern double robotPosX;
extern double robotPosY;
extern double robotRotation;
extern double robotSizeFB;
extern double robotSizeLR;
extern double remainingDistance;
extern double speedFactor;
extern double wheelDiameter;
extern double gearRatio;
extern double oneInch;
extern double oneTile;
extern int autonDriveSpeed;