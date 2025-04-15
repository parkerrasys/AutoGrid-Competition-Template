using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern inertial Inertial;
extern light LightA;
extern digital_out DigitalOutB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );