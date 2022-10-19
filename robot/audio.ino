// FFT data
#define SAMPLES 256
#define SAMPLE_FREQ 12000       // Nyquist Frequency
arduinoFFT fft = arduinoFFT();
unsigned int samplePeriod = round(1000000.0/SAMPLE_FREQ);   // Delay between samples
unsigned long sampleStartTime;  // To make the collected samples come at equal, discrete time intervals
double vReal[SAMPLES];          // To hold the raw analog data from the microphone
double vImag[SAMPLES];          // To make the FFT happy

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
