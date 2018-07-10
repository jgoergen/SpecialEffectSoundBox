void voice_init() {

  sine1.amplitude(0.5); // 0 to 1
  mixer2.gain(0, 1.0);
  delay1.delay(0, 500); // channel, milliseconds
  delay1.delay(1, 500); // channel, milliseconds
  delay1.delay(2, 500); // channel, milliseconds
  delay1.disable(3);
  delay1.disable(4);
  delay1.disable(5);
  delay1.disable(6);
  delay1.disable(7);
}

void voice_setVolume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */
  float remappedAmount = map(amount, 0, 100, 0, 4);
  mixer1.gain(0, remappedAmount);
}

void voice_setReverb(int amount) {
  
  float remappedAmount = map(amount, 0, 100, 0, 10);
  reverb1.reverbTime(amount); // seconds
}

void voice_setDelay(int amount) {

  float remappedAmount = map(amount, 0, 100, 0, 4);
  mixer2.gain(1, remappedAmount);
  mixer2.gain(2, remappedAmount);
  mixer2.gain(3, remappedAmount);
}

void voice_setPitch(int frequency) {

  /*
  Set the frequency, from 0 to 22000. 
  Very low values may be used to create a LFO (Low Frequency Oscillator) for objects with modulation signal inputs.
  */
  float remappedAmount = map(frequency, 0, 100, 5000, 20000);
  sine1.frequency(frequency);
}

