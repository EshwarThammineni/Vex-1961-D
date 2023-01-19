#include "main.h"
#include "pros/rtos.hpp"

const float PI = 3.141592653;

void driveAll(bool direction, int speedPct) {
  if (direction) {
    backLeftDrive.move_velocity(2 * speedPct);
    frontLeftDrive.move_velocity(2 * speedPct);
    backRightDrive.move_velocity(2 * speedPct);
    frontRightDrive.move_velocity(2 * speedPct);
  } else {
    backLeftDrive.move_velocity(-2 * speedPct);
    frontLeftDrive.move_velocity(-2 * speedPct);
    backRightDrive.move_velocity(-2 * speedPct);
    frontRightDrive.move_velocity(-2 * speedPct);
  }
}

int inches2delay(int inches) { return 2.1 * inches / ((11 * PI) / 1200); }

float degrees2delay(float degrees) {
  return (10.0 / 9.0) * (12.0 / 2.0 * degrees / (6.0 / 5.0));
}

void driveStop() {
  backLeftDrive.move_velocity(0);
  frontLeftDrive.move_velocity(0);
  backRightDrive.move_velocity(0);
  frontRightDrive.move_velocity(0);
}

void moveForward(int inches) {
  frontLeftDrive.move_velocity(200);
  frontRightDrive.move_velocity(200);
  backLeftDrive.move_velocity(200);
  backRightDrive.move(200);
  pros::delay(inches2delay(inches));
  driveStop();
}

void moveRight(int inches) {
  frontLeftDrive.move_velocity(200);
  frontRightDrive.move_velocity(-200);
  backRightDrive.move_velocity(200);
  backLeftDrive.move_velocity(-200);
  pros::delay(inches2delay(inches));
  driveStop();
}

void moveBackward(int inches) {
  frontLeftDrive.move_velocity(-190);
  frontRightDrive.move_velocity(-200);
  backLeftDrive.move_velocity(-190);
  backRightDrive.move(-200);
  pros::delay(inches2delay(inches));
  driveStop();
}

void moveLeft(int inches) {
  frontLeftDrive.move_velocity(-200);
  frontRightDrive.move_velocity(200);
  backRightDrive.move_velocity(-200);
  backLeftDrive.move_velocity(200);
  pros::delay(inches2delay(inches));
  driveStop();
}

void rotate(bool reverse, int degrees) {
  // Left to right
  if (!reverse) {
    frontLeftDrive.move_velocity(-200);
    frontRightDrive.move_velocity(200);
    backRightDrive.move_velocity(200);
    backLeftDrive.move_velocity(-200);
    pros::delay(degrees2delay(degrees));
    driveStop();
  } else {
    frontLeftDrive.move_velocity(200);
    frontRightDrive.move_velocity(-200);
    backRightDrive.move_velocity(-200);
    backLeftDrive.move_velocity(200);
    pros::delay(degrees2delay(degrees));
    driveStop();
  }
}

/*
class DriveTrainX {
public:
  void moveForward(int delay) {
    frontLeftDrive.move_velocity(200);
    frontRightDrive.move_velocity(200);
    backLeftDrive.move_velocity(200);
    backRightDrive.move(200);
    pros::delay(delay);
  }
  void moveRight(int delay) {
    frontLeftDrive.move_velocity(200);
    frontRightDrive.move_velocity(-200);
    backRightDrive.move_velocity(200);
    backLeftDrive.move_velocity(-200);
    pros::delay(delay);
  }
  void moveBackward(int delay) {
    frontLeftDrive.move_velocity(-200);
    frontRightDrive.move_velocity(-200);
    backLeftDrive.move_velocity(-200);
    backRightDrive.move(-200);
    pros::delay(delay);
  }
  void moveLeft(int delay) {
    frontLeftDrive.move_velocity(-200);
    frontRightDrive.move_velocity(200);
    backRightDrive.move_velocity(-200);
    backLeftDrive.move_velocity(200);
    pros::delay(delay);
  }
};
*/