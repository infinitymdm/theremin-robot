#define MIC_IN 3        // Analog input from microphone module
#define MIC_ACTIVITY 6  // Digital input from microphone module
#define L_MOTOR 10      // Digital motor control output
#define R_MOTOR 9       // Digital motor control output

void setup() {
  // Set up pins
  pinMode(MIC_IN, INPUT);
  pinMode(MIC_ACTIVITY, INPUT);
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);

  // Initialize with motors off
  stop();
}

void loop() {
  turnRight();
  delay(1000);
  stop();
  delay(500);
  turnLeft();
  delay(1000);
  stop();
  delay(100);
}

// Turn the left motor and the right motor equally
void go() {
  setLeftMotor(HIGH);
  setRightMotor(HIGH);
}

// Stop both motors
void stop() {
  setLeftMotor(LOW);
  setRightMotor(LOW);
}

// Turn the left motor less than the right motor to turn left
void turnLeft() {
  setLeftMotor(LOW);
  setRightMotor(HIGH);
}

// Turn the left motor more than the right motor to turn right
void turnRight() {
  setRightMotor(LOW);
  setLeftMotor(HIGH);
}

// Abstract left motor
// TODO: add an LED
void setLeftMotor(bool mode) {
  digitalWrite(L_MOTOR, !mode);
}

// Abstract right motor
// TODO: add an LED
void setRightMotor(bool mode) {
  digitalWrite(R_MOTOR, !mode);
}
