#define MIC_IN PIN_A3   // Analog input from microphone module
#define MIC_ACTIVE PIN_A6   // Digital input from microphone module
#define L_MOTOR PIN_A10 // Digital motor control output
#define R_MOTOR PIN_A9  // Digital motor control output

void setup() {
  // Set up pins
  pinMode(MIC_IN, INPUT);
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);

  // Initialize with motors off
  digitalWrite(L_MOTOR, HIGH);
  digitalWrite(R_MOTOR, HIGH);
}

void loop() {
  digitalWrite(L_MOTOR, LOW);
  delay(2000);
  digitalWrite(L_MOTOR, HIGH);
  delay(500);
  digitalWrite(R_MOTOR, LOW);
  delay(2000);
  digitalWrite(R_MOTOR, HIGH);
  delay(500);

//  if(MIC_IN >= X)
//    turnLeft();

//  else if (MIC_IN <= Y)
//    turnRight();
  
//  else if (MIC_IN == Z)
//    stopRobot();

//  else
//    goForward();
}

// Turn the left motor and the right motor equally
void goForward(){
  digitalWrite(L_MOTOR, HIGH);
  digitalWrite(R_MOTOR, HIGH);
}

// Stop both motors
void stopRobot(){
  digitalWrite(L_MOTOR, LOW);
  digitalWrite(R_MOTOR, LOW);
}

// Turn the left motor less than the right motor to turn left
void turnLeft(){
  digitalWrite(L_MOTOR, LOW);
  digitalWrite(R_MOTOR, HIGH);
}

// Turn the left motor more than the right motor to turn right
void turnRight(){
  digitalWrite(L_MOTOR, HIGH);
  digitalWrite(R_MOTOR, LOW);  
}
