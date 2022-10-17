#include "arduinoFFT.h"

// Pin definitions
#define MIC_ACTIVITY D2  // Digital input from microphone module
#define MIC_IN A3        // Analog input from microphone module
#define L_MOTOR D10      // Digital motor control output
#define R_MOTOR D9       // Digital motor control output

// FFT data
#define SAMPLES 256
#define SAMPLE_FREQ 12000
arduinoFFT fft = arduinoFFT();
unsigned int samplePeriod;
unsigned long sampleStartTime;
double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
  // Set up pins
  pinMode(MIC_IN, INPUT);
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);

  // Initialize with motors off
  stop();

  // Open Serial port for monitoring
  Serial.begin(115200);

  // Calculate delay between samples
  samplePeriod = round(1000000.0/SAMPLE_FREQ);
}

double peak;
void loop() {
  peak = getPeakFrequency();
  Serial.println(peak);

  // Decide which direction to turn based on peak location
  // TODO
}

double getPeakFrequency() {
  // Collect samples
  for (int i = 0; i < SAMPLES; i++) {
    sampleStartTime = micros();

    vReal[i] = analogRead(MIC_IN);
    vImag[i] = 0;

    // Wait until one sample period has passed
    while (micros() < (sampleStartTime + samplePeriod));
  }
  
  // Perform FFT on samples
  fft.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  fft.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  fft.ComplexToMagnitude(vReal, vImag, SAMPLES);

  // Identify peak frequency
  return fft.MajorPeak(vReal, SAMPLES, SAMPLE_FREQ);
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
