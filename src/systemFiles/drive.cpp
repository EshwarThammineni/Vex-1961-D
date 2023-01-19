#include "main.h"

// MOTORS
pros::Motor backLeftDrive(backLeftDrivePort, pros::E_MOTOR_GEARSET_18, false,
                          pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor frontLeftDrive(frontLeftDrivePort, pros::E_MOTOR_GEARSET_18, false,
                           pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backRightDrive(backRightDrivePort, pros::E_MOTOR_GEARSET_18, true,
                           pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor frontRightDrive(frontRightDrivePort, pros::E_MOTOR_GEARSET_18, true,
                            pros::E_MOTOR_ENCODER_COUNTS);
// CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// How to Move Cardinal Directions with X-drive
// Forward - All Motors Positive Direction
// Northeast - All Motors Positive, but low frontright and backleft and high
// frontleft and back right Right - Positive frontLeftDrive, Negative
// frontRightDrive, Positive backRightDrive, Negative backLeftDrive Southeast -
// ALl Motors Negative, but low frontright and backleft and high frontleft and
// backright Backward - All Motors Negative Direction Southwest - All Motors
// Negative, but low frontleft and backright and high frontright and backleft
// Left - Negative frontLeftDrive, Positive frontRightDrive, Negative
// backRightDrive, Positive backLeftDrive Northwest - All Motors Positive, but
// low frontleft and backright and high frontright and backleft

// Left to right Rotation - Negative frontLeftDrive, Positive frontRightDrive
// and backright, Negative backleftDrive Right to left Rotation - Positive
// frontLeftDrive, Negative frontRightDrive and backright, Positive
// backleftDrive STATUS BOOLS
bool DrivetrainLeftNeedsToBeStopped = true;
bool DrivetrainRightNeedsToBeStopped = true;

// Right Joystick is for rotation

int motorResponseDrive(int motor, int x, int y, int z) {
  // Motor1 is frontleft
  if (motor == 1) {
    return x + y + z;
  }
  // Motor2 is frontright
  if (motor == 2) {
    return y - x - z;
  }
  // Motor3 is backright
  if (motor == 3) {
    return x + y - z;
  }
  // Motor4 is backleft
  if (motor == 4) {
    return y - x + z;
  }
  return 0;
}

// JOYSTICK MAPPING
void doubleArcade() {
  int leftJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  int leftJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  // Using L1 R1 for rotation
  bool R1Pressed = controller.get_digital(DIGITAL_R1);
  bool L1Pressed = controller.get_digital(DIGITAL_L1);
  // Zone where input is considered 0
  if (leftJoystickX > -5 && leftJoystickX < 5) {
    leftJoystickX = 0;
  }
  if (leftJoystickY > -5 && leftJoystickY < 5) {
    leftJoystickY = 0;
  }

  // motor usage is based on the motorResponseDrive function
  frontLeftDrive.move_velocity(
      2 * motorResponseDrive(1, leftJoystickX, leftJoystickY, rightJoystickX));
  frontRightDrive.move_velocity(
      2 * motorResponseDrive(2, leftJoystickX, leftJoystickY, rightJoystickX));
  backRightDrive.move_velocity(
      2 * motorResponseDrive(3, leftJoystickX, leftJoystickY, rightJoystickX));
  backLeftDrive.move_velocity(
      2 * motorResponseDrive(4, leftJoystickX, leftJoystickY, rightJoystickX));
}
/*
void doubleArcade() {
  int drivetrainLeftSideSpeed =
controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); int
drivetrainRightSideSpeed =
controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  if (abs(drivetrainLeftSideSpeed) < 5) {
    if (DrivetrainLeftNeedsToBeStopped == true) {
      backRightDrive.move_velocity(0);
      frontRightDrive.move_velocity(0);
      DrivetrainLeftNeedsToBeStopped = false;
    }
  } else {
      DrivetrainLeftNeedsToBeStopped = true;
    }

  if (abs(drivetrainRightSideSpeed) < 5) {
    if (DrivetrainRightNeedsToBeStopped) {
      backLeftDrive.move_velocity(0);
      frontLeftDrive.move_velocity(0);
      DrivetrainRightNeedsToBeStopped = false;
    }
  } else {
      DrivetrainRightNeedsToBeStopped = true;
  }

  if(drivetrainLeftSideSpeed > 100){
    drivetrainLeftSideSpeed  = 100;
  }else if (drivetrainLeftSideSpeed < -100){
    drivetrainLeftSideSpeed  = -100;
  }
  if(drivetrainRightSideSpeed > 100){
    drivetrainRightSideSpeed  = 100;
  }else if (drivetrainRightSideSpeed < -100){
    drivetrainRightSideSpeed  = -100;
  }

  if (DrivetrainLeftNeedsToBeStopped) {
      backLeftDrive.move_velocity(drivetrainLeftSideSpeed * 6);
      frontLeftDrive.move_velocity(drivetrainLeftSideSpeed * 6);
  }

  if (DrivetrainRightNeedsToBeStopped) {
      backRightDrive.move_velocity(drivetrainRightSideSpeed * 6);
      frontRightDrive.move_velocity(drivetrainRightSideSpeed * 6);
  }
}
*/