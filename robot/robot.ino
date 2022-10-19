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

int TURN_LEFT_FREQ = 2300;  // Hertz. Threshold that the detected frequency must be less than to turn left
int TURN_RIGHT_FREQ = 2400; // Hertz. Threshold that the detected frequency must be greater than to turn right

// To control on-board RGB LED
int LED_Power = 11;     // On-board RGB LED
int LED_PIN = 12;     // On-board RGB LED
int NUMPIXELS = 1;      // Number of LEDs (Pixels) for the NeoPixel to control
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// For smoothing the data
const int numReadings = 10; // value to determine the size of the readings array
int readings[numReadings];  // the last numReadings readings from the analog input
int readIndex = 0;          // the index of the current reading

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

  // initialize all the smoothing readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  pixels.clear(); // Turn off the internal LED
  peak = getPeakFrequency();
  //Serial.println(peak);
  readings[readIndex] = peak; // Add latest peak reading to the array by overwriting the oldest reading
  readIndex = readIndex + 1;  // advance to the next position in the array:
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  int smoothedPeak = calculateSmoothedPeak();
  Serial.println(smoothedPeak);
  // Decide which direction to turn based on peak location
  if (smoothedPeak > TURN_LEFT_FREQ & smoothedPeak < TURN_RIGHT_FREQ)
    turnLeft();
  else if (smoothedPeak > TURN_RIGHT_FREQ)
    turnRight();
  else
    goForward();
}

int calculateSmoothedPeak(){
  int smoothedPeak = 0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    smoothedPeak = smoothedPeak + readings[thisReading];
  }
  return smoothedPeak/numReadings;
}

void setRGBColor(int R, int G, int B){
  pixels.clear(); // Turn off the on-board LED
  pixels.setPixelColor(0, pixels.Color(R,G,B));   // change the on-board LED to the specified color
  pixels.show();  // Write the color to the RGB LED
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
// TODO: add an LED
void setLeftMotor(bool mode) {
  digitalWrite(L_MOTOR, !mode);
}

// Abstract right motor
// TODO: add an LED
void setRightMotor(bool mode) {
  digitalWrite(R_MOTOR, !mode);
}
