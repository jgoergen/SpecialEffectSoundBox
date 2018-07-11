#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];

void voice_init() {

  Serial.print("Voice...");
  mixer2.gain(0, 1.0);
  voice_setVolume(50);
  // the Granular effect requires memory to operate
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  voice_setPitch(30);
  voice_setReverb(40);
  voice_setReverbVolume(10);
}

void voice_setVolume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */
  float remappedAmount = (float)map(volume, 0, 100, 0, 200) / 100.0;
  Serial.print("Setting voice volume to ");
  Serial.println(remappedAmount);
  mixer1.gain(0, remappedAmount);
}

void voice_setReverb(int amount) {
  
  int remappedAmount = map(amount, 0, 100, 0, 8);
  Serial.print("Setting voice reverb to ");
  Serial.println(remappedAmount);
  reverb1.reverbTime(amount); // seconds
}

void voice_setReverbVolume(int amount) {

  float remappedAmount = (float)map(amount, 0, 100, 0, 100) / 100.0;
  Serial.print("Setting voice reverb volume to ");
  Serial.println(remappedAmount);
  mixer2.gain(0, remappedAmount);
}

void voice_setPitch(int frequency) {

  float remappedAmount = (float)map(frequency, 0, 100, 1, 10) / 10.0;
  Serial.print("Setting voice pitch to ");
  Serial.println(remappedAmount);
  float grainSpeed = remappedAmount; // ( 0.1 - 1.0 )
  granular1.beginPitchShift(25.0 + (grainSpeed * 75.0));
  float speedRatio = remappedAmount; // 0.5 to 2.0
  granular1.setSpeed(powf(2.0, speedRatio * 2.0 - 1.0));
}

