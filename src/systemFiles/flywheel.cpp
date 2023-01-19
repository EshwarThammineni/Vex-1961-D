#include "main.h"
#include "pros/rtos.h"

using pros::E_CONTROLLER_DIGITAL_B;
using pros::E_CONTROLLER_DIGITAL_X;

pros::Motor flywheelMotorA(16, pros::E_MOTOR_GEARSET_18, true,
                           pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheelMotorB(19, pros::E_MOTOR_GEARSET_18, false,
                           pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheelMotorC(10, pros::E_MOTOR_GEARSET_18, true,
                           pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor_Group flywheel({flywheelMotorA, flywheelMotorB, flywheelMotorC});

int flywheelSpeed = 199;
bool flywheelState = false;
bool Controller1L1ControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;

// L1 flywheel Mapping
void flywheelControl() {
  if (controller.get_digital(E_CONTROLLER_DIGITAL_X)) {
    if (flywheelSpeed < 199) {
      flywheelSpeed += 1;
    }
    Controller1XBButtonsControlMotorsStopped = false;
  } else if (controller.get_digital(E_CONTROLLER_DIGITAL_B)) {
    if (flywheelSpeed > 40) {
      flywheelSpeed -= 1;
    }
    Controller1XBButtonsControlMotorsStopped = false;
  } else if (!Controller1XBButtonsControlMotorsStopped) {
    Controller1XBButtonsControlMotorsStopped = true;
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    flywheelState = !flywheelState;
    pros::c::delay(100);
    Controller1L1ControlMotorsStopped = false;
  } else if (!Controller1L1ControlMotorsStopped) {
    Controller1L1ControlMotorsStopped = true;
  }

  if (flywheelState) {
    flywheel.move_velocity(flywheelSpeed);
  } else {
    flywheel.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    flywheel.brake();
  }
  int flywheelPct = flywheelSpeed / 2;
  controller.print(1, 0, "FlyWheel Pct: %d", flywheelPct);
}
