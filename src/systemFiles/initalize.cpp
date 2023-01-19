#include "main.h"

void resetRobot(){
  controller.clear();
  flywheel.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  flywheel.tare_position();
  intake.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  intake.tare_position();
  backLeftDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  backLeftDrive.tare_position();
  frontLeftDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  frontLeftDrive.tare_position();
  backRightDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  backRightDrive.tare_position();
  frontRightDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  frontRightDrive.tare_position();
}