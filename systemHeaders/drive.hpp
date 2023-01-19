#include "main.h"

enum MOTOR_PORTS {
  backLeftDrivePort = 17,
  frontLeftDrivePort = 18,
  backRightDrivePort = 11,
  frontRightDrivePort = 15
};

// MOTORS
extern pros::Motor backLeftDrive;
extern pros::Motor frontLeftDrive;
extern pros::Motor backRightDrive;
extern pros::Motor frontRightDrive;

// CONTROLLER
extern pros::Controller controller;

// OPCONTROL HEADERS
void doubleArcade();
void motorRotateCounterClockwise();
void motorRotateClockwise();
int motorResponseDrive(int motor, int x, int y);
