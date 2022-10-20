/*
// Theremin-Controlled Robot (Frequency Controlled Robot)
// Authors: Peter Moyer & Marcus Mellor 
//
// Description: This project defines the software portion of a robot that is designed to operate 
//    on the SEEEDStudio XIAO RP2040. It receives input from a microphone and processes it to 
//    determine the peak frequency. Peak frequencies are smoothed with an averaging function, 
//    and then the smoothed peak frequency is used to determine how the robot should drive the
//    motors to move the robot.
// 
// License: MIT
//
// Thanks to Clyde Lettsome for his post that gave me direction on how to use arduinoFFT
// https://create.arduino.cc/projecthub/lbf20012001/audio-frequency-detector-617856
*/
#include "arduinoFFT.h"
#include "Adafruit_NeoPixel.h"

// Pin definitions
#define MIC_ACTIVITY D2  // Digital input from microphone module
#define MIC_IN A3        // Analog input from microphone module
#define L_MOTOR D10      // Digital motor control output
#define R_MOTOR D9       // Digital motor control output

// To control on-board RGB LED
int LED_Power = 11;     // On-board RGB LED
int LED_PIN = 12;       // On-board RGB LED
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
  stop();                       // initialize robot with motors off

  // Open Serial port for monitoring
  Serial.begin(115200);

  //Allow the on-board RGB LED to be controlled
  digitalWrite(LED_Power, HIGH);

  // initialize all the smoothing readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

// Threshold Frequencies to control the robot
int TURN_LEFT_FREQ  = 2300; // Hertz. Threshold that the detected frequency must be less than to turn left
int TURN_RIGHT_FREQ = 2600; // Hertz. Threshold that the detected frequency must be greater than to turn right
int END_FREQ        = 2900; // Hertz. The robot will use its default behavior for frequencies greater than this threshold value
double frequency;           // Holds the current measured frequency

void loop() {
  pixels.clear(); // Turn off the internal LED
  frequency = getPeakFrequency();
  readings[readIndex] = frequency; // Add latest peak reading to the array by overwriting the oldest reading
  readIndex++; // advance to the next position in the array:
  
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  
  frequency = calculateSmoothedPeak();
  Serial.println(frequency); // Print the filtered frequency data

  // Decide which direction to turn based on smoothed peak frequency
  if (frequency > TURN_LEFT_FREQ & frequency < TURN_RIGHT_FREQ)
    turnLeft();
  else if (frequency > TURN_RIGHT_FREQ & frequency < END_FREQ)
    turnRight();
  else
    goForward();
}


double calculateSmoothedPeak(){
  double sumOfPeaks = 0.0; // Sum of all the peaks in the readings array
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    sumOfPeaks += readings[thisReading];
  }
  return sumOfPeaks/numReadings; // Return the smoothedPeak value, which is the average frequency value in the readings array
}


void setRGBColor(int R, int G, int B){
  pixels.clear(); // Turn off the on-board LED
  pixels.setPixelColor(0, pixels.Color(R,G,B));   // change the on-board LED to the specified color
  pixels.show();  // Write the color to the RGB LED
}
