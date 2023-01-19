#include "main.h"

bool PIDEnabled;
int leftPrevError;
int rightPrevError;
int leftTotalError;
int rightTotalError;
int leftTargetValue;
int rightTargetValue;

void driveTo(int leftInch, int rightInch) {
  PIDEnabled = true;
  backLeftDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  backLeftDrive.tare_position();
  frontLeftDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  frontLeftDrive.tare_position();
  backRightDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  backRightDrive.tare_position();
  frontRightDrive.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
  frontRightDrive.tare_position();
    leftTargetValue = 59 * leftInch;
    rightTargetValue = 59 * rightInch;
    while(PIDEnabled){
        //Tune here 
        double leftkP = 0.585;
        double leftkI = 0.0005;
        double leftkD = 0.005;

        double rightkP = 0.6;
        double rightkI = 0.0005;
        double rightkD = 0.005;

        double leftDrivePosition = (backLeftDrive.get_position() + frontLeftDrive.get_position()) / 2;
        double rightDrivePosition = (backRightDrive.get_position() + frontRightDrive.get_position()) / 2;

        int leftDriveError = leftTargetValue - leftDrivePosition;
        int rightDriveError = rightTargetValue - rightDrivePosition;  

        if (abs(leftDriveError) < 5 && abs(rightDriveError) < 5){
            PIDEnabled = false;
        }
        
        int leftDriveDerivative = leftDriveError - leftPrevError;
        int rightDriveDerivative = rightDriveError - rightPrevError;

        leftTotalError += leftDriveError;  
        rightTotalError += rightDriveError;  

        if(abs(leftTotalError) > 300){
            leftTotalError = 0;
        }
        if(abs(rightTotalError) > 300){
            rightTotalError = 0;
        }

        int leftMotorPower = ((leftDriveError * leftkP) + (leftTotalError * leftkI) + (leftDriveDerivative * leftkD));
        int rightMotorPower = ((rightDriveError * rightkP) + (rightTotalError * rightkI) + (rightDriveDerivative * rightkD));
        
        
        backLeftDrive.move_velocity(leftMotorPower);
        frontLeftDrive.move_velocity(leftMotorPower);
        backRightDrive.move_velocity(rightMotorPower);
        frontRightDrive.move_velocity(rightMotorPower);
        
        
        leftPrevError = leftDriveError;
        rightPrevError = rightDriveError;

        pros::Task::delay(10);  
    }
    
}