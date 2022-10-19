#include "arduinoFFT.h"
#include "Adafruit_NeoPixel.h"

// Pin definitions
#define MIC_ACTIVITY D2  // Digital input from microphone module
#define MIC_IN A3        // Analog input from microphone module
#define L_MOTOR D10      // Digital motor control output
#define R_MOTOR D9       // Digital motor control output

// FFT data
#define SAMPLES 256
#define SAMPLE_FREQ 12000       // Nyquist Frequency
arduinoFFT fft = arduinoFFT();
unsigned int samplePeriod;
unsigned long sampleStartTime;
double vReal[SAMPLES];        
double vImag[SAMPLES];
double peak;                    // To hold the peak frequency value of from the FFT to use in calculations and to output to the serial monitor

// To control on-board RGB LED
int LED_Power = 11;     // On-board RGB LED
int LED_PIN = 12;     // On-board RGB LED
int NUMPIXELS = 1;      // Number of LEDs (Pixels) for the NeoPixel to control
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Set up pins
  pinMode(MIC_IN, INPUT);       // initialize microphone pin for analog input
  pinMode(L_MOTOR, OUTPUT);     // initialize left motor pin
  pinMode(R_MOTOR, OUTPUT);     // initialize right motor pin
  pinMode(LED_Power, OUTPUT);   // initialize internal RGB LED pin
  stop();                       // Initialize with motors off

  // Open Serial port for monitoring
  Serial.begin(115200);

  // Calculate delay between samples
  samplePeriod = round(1000000.0/SAMPLE_FREQ);

  digitalWrite(LED_Power, HIGH);  //Allow the on-board RGB LED to be controlled
}

void loop() {
  pixels.clear(); // Turn off the internal LED
  peak = getPeakFrequency();
  Serial.println(peak);
  pixels.setPixelColor(0, pixels.Color(255,0,0));   // turn the internal LED on RED
  delay(500);                       // wait for a second
  pixels.show();
  pixels.clear(); // Turn off the internal LED
  pixels.setPixelColor(0, pixels.Color(0,255,0));   // turn the internal LED on GREEN
  delay(500);                       // wait for a second
  pixels.show();
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
