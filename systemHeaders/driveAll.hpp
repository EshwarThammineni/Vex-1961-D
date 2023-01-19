#include "main.h"
// MOTORS

// CONTROLLER

// FUNCTION HEADERS
void driveAll(bool direction, int speed);
int inches2delay(int inches);
void driveStop();

void moveForward(int inches);
void moveRight(int inches);
void moveBackward(int inches);
void moveLeft(int inches);
void rotate(bool reverse, int degrees);
