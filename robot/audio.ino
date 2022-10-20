// FFT data
#define SAMPLES 256
#define SAMPLE_FREQ 12000       // Nyquist Frequency is half this
arduinoFFT fft = arduinoFFT();
unsigned int samplePeriod = round(1000000.0/SAMPLE_FREQ);   // Delay between samples
unsigned long sampleStartTime;  // To make the collected samples come at equal, discrete time intervals

const float alpha = 0.3;        // Filter coefficient
double micRead[SAMPLES];        // To hold the raw analog data from the microphone
double vReal[SAMPLES];          // To hold the filtered data from the microphone
double vImag[SAMPLES];          // To make the FFT happy

// Read in, filter, and save the peak frequency sent by the microphone
double getPeakFrequency() {
  // Collect samples
  for (int i = 0; i < SAMPLES; i++) {
    sampleStartTime = micros();

    micRead[i] = analogRead(MIC_IN);
    vImag[i] = 0;
    // Filter the analog data
    highpassFilter(i); // Sets vReal[i] with the filtered version of the data in micRead[i]
    
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

void highpassFilter(int i){
  // [SAMPLES - 1] gives the last data point from the previous sample set
  if (i == 0){ vReal[i] = alpha * (vReal[SAMPLES - 1] + micRead[i] - micRead[SAMPLES - 1]); } // Handle first case without falling off the array
  else { vReal[i] = alpha * (vReal[i-1] + micRead[i] - micRead[i-1]); }

}

void lowpassFilter(int i){
  // [SAMPLES - 1] gives the last data point from the previous sample set
  if (i == 0){ vReal[i] = alpha * micRead[i] + (1 - alpha) * vReal[SAMPLES - 1]; } // Handle first case without falling off the array
  else { vReal[i] = alpha * micRead[i] + (1 - alpha) * vReal[i-1]; }
  
}
