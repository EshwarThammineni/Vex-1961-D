#include "main.h"

bool state = false;
pros::ADIDigitalOut launcher(1, state);

bool Controller1L2ControlMotorsStopped = true;

// L2 Launcher Mapping
void launcherControl() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    state = false;
    launcher.set_value(state);
    Controller1L2ControlMotorsStopped = false;
  } else if (!Controller1L2ControlMotorsStopped) {
    state = true;
    launcher.set_value(state);
    Controller1L2ControlMotorsStopped = true;
  }
}