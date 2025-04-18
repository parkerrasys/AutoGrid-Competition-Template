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
void setGearRatio(double inputGear, double outputGear);

//Paths
void red1();
void red2(); 
void red3();
void blue1();
void blue2();
void blue3();

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