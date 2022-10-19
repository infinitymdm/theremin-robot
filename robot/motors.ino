// Functions for controlling the motors

// Turn the left motor and the right motor equally
void goForward() {
  setRGBColor(0,0,255);   // set the on-board LED to BLUE
  setLeftMotor(HIGH);
  setRightMotor(HIGH);
}


// Stop both motors
void stop() {
  setRGBColor(255,255,255);   // set the on-board LED to WHITE
  setLeftMotor(LOW);
  setRightMotor(LOW);
}


// Turn the right motor more than the left motor to turn left
void turnLeft() {
  setRGBColor(255,0,0);   // set the on-board LED to RED
  setLeftMotor(LOW);
  setRightMotor(HIGH);
}


// Turn the left motor more than the right motor to turn right
void turnRight() {
  setRGBColor(0,255,0);   // set the on-board LED to GREEN
  setRightMotor(LOW);
  setLeftMotor(HIGH);
}


// Abstract left motor
void setLeftMotor(bool mode) {
  digitalWrite(L_MOTOR, !mode);
}


// Abstract right motor
void setRightMotor(bool mode) {
  digitalWrite(R_MOTOR, !mode);
}
