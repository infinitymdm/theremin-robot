#define MIC_IN PIN_A6   // Digital input from microphone module
#define L_MOTOR PIN_A10 // Digital motor control output
#define R_MOTOR PIN_A9  // Digital motor control output

void setup() {
  // Set up pins
  pinMode(MIC_IN, INPUT);
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);

  // Initialize with motors off
  digitalWrite(L_MOTOR, LOW);
  digitalWrite(R_MOTOR, LOW);
}

void loop() {
  digitalWrite(L_MOTOR, HIGH);
  delay(250);
  digitalWrite(R_MOTOR, HIGH);
  delay(250);
  digitalWrite(R_MOTOR, LOW);
  delay(250);
  digitalWrite(L_MOTOR, LOW);
  delay(250);
}
