#include "main.h"

bool expandstate = false; 
pros::ADIDigitalOut expander(2, expandstate);

//Down Button expander Mapping
void expanderControl(){
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
    expandstate = true;
    expander.set_value(expandstate);
    flywheel.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    flywheel.brake();
  }
}