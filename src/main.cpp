#include "main.h"
#include "pros/colors.h"
#include <algorithm>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
bool color = true;
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  color = !color;
  if (pressed) {
    pros::lcd::set_text(2, "Blue");
    pros::lcd::set_background_color(0, 0, 255);

  } else {
    pros::lcd::set_text(2, "Red");
    pros::lcd::set_background_color(255, 0, 0);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(0, "*****                     **");
  pros::lcd::set_text(1, "**   **                   **");
  pros::lcd::set_text(2, "**   **                   **");
  pros::lcd::set_text(3, "*****    ** ***  **   **  ** **");
  pros::lcd::set_text(4, "**   **  ***  ** **   **  **   **");
  pros::lcd::set_text(5, "**   *** **      **   **  **   **");
  pros::lcd::set_text(6, "**   **  **      **   **  **   **");
  pros::lcd::set_text(7, "******   **        ***    **   **");
  pros::lcd::register_btn1_cb(on_center_button);
  resetRobot();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  controller.clear();
  resetRobot();
  launcher.set_value(true);
  moveBackward(12);
  driveStop();
  /*
  intake.move_velocity(-200);
  pros::delay(100);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  flywheel.move_velocity(200);
  pros::delay(2000);
  launcher.set_value(false);
  pros::delay(150);
  launcher.set_value(true);
  pros::delay(1000);
  launcher.set_value(false);
  flywheel.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
  flywheel.move_velocity(0);
  launcher.set_value(true);
  intake.brake();
  launcher.set_value(false);
  */
  // moveLeft(0);
  // moveForward(0);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  while (true) {
    // Controller Settings
    // Double-Arcade Drive
    doubleArcade();
    // Intake Buttons
    intakeControl();
    flywheelControl();
    launcherControl();
    resetRobot();
    expanderControl();

    pros::delay(10);
  }
}
