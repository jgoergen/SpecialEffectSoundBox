void voice_init() {

  sine1.amplitude(1); // 0 to 1
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
  
  mixer1.gain(0, 0);
}

void voice_setPresence(int amount) {

  // reverb1.reverbTime(0); // seconds
  // delay1.delay(0, 0); // channel, milliseconds
  // mixer2.gain(0, 0);
  
  // delay1.delay(1, 0); // channel, milliseconds
  // mixer2.gain(1, 0);
  
  // delay1.delay(2, 0); // channel, milliseconds
  // mixer2.gain(2, 0);
  
  // delay1.delay(3, 0); // channel, milliseconds
  // mixer2.gain(3, 0);
}

void voice_setTone(int frequency) {

  /*
  Set the frequency, from 0 to 22000. 
  Very low values may be used to create a LFO (Low Frequency Oscillator) for objects with modulation signal inputs.
  */
  
  sine1.frequency(frequency);
}

