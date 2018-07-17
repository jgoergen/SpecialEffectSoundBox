#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
int currentVoiceVolume = 50;
int currentVoicePitch = 30;
int currentVoiceReverb = 30;
int currentVoiceReverbVolume = 10;

void voice_init() {

  Serial.print("Voice...");
  voice_setVolume(currentVoiceVolume);
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  voice_setPitch(currentVoicePitch);
  voice_setReverb(currentVoiceReverb);
  voice_setReverbVolume(currentVoiceReverb);
}

void voice_lowerVolume() {

  currentVoiceVolume -= 10;
  if (currentVoiceVolume < 0)
    currentVoiceVolume = 0;

  Serial.print("lowering voice volume to ");
  Serial.println(currentVoiceVolume);

  voice_setVolume(currentVoiceVolume);
}

void voice_raiseVolume() {

  currentVoiceVolume += 10;
  if (currentVoiceVolume > 100)
    currentVoiceVolume = 100;

  Serial.print("raising voice volume to ");
  Serial.println(currentVoiceVolume);

  voice_setVolume(currentVoiceVolume);
}

void voice_setVolume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */

  currentVoiceVolume = volume;
  float remappedAmount = (float)map(volume, 0, 100, 0, 300) / 100.0;
  Serial.print("Setting voice volume to ");
  Serial.println(remappedAmount);
  mixer1.gain(0, remappedAmount);
}

void voice_lowerReverb() {

  currentVoiceReverb -= 10;
  if (currentVoiceReverb < 0)
    currentVoiceReverb = 0;

  Serial.print("lowering voice reverb to ");
  Serial.println(currentVoiceReverb);

  voice_setReverb(currentVoiceReverb);
}

void voice_raiseReverb() {

  currentVoiceReverb += 10;
  if (currentVoiceReverb > 100)
    currentVoiceReverb = 100;

  Serial.print("raising voice reverb to ");
  Serial.println(currentVoiceReverb);

  voice_setReverb(currentVoiceReverb);
}

void voice_setReverb(int amount) {

  currentVoiceReverb = amount;
  int remappedAmount = map(amount, 0, 100, 0, 8);
  Serial.print("Setting voice reverb to ");
  Serial.println(remappedAmount);
  reverb1.reverbTime(amount); // seconds
}

void voice_lowerReverbVolume() {

  currentVoiceReverbVolume -= 10;
  if (currentVoiceReverbVolume < 0)
    currentVoiceReverbVolume = 0;

  Serial.print("lowering voice reverb volume to ");
  Serial.println(currentVoiceReverbVolume);
  
  voice_setReverbVolume(currentVoiceReverbVolume);
}

void voice_raiseReverbVolume() {

  currentVoiceReverbVolume += 10;
  if (currentVoiceReverbVolume > 100)
    currentVoiceReverbVolume = 100;

  Serial.print("raising voice reverb volume to ");
  Serial.println(currentVoiceReverbVolume);

  voice_setReverbVolume(currentVoiceReverbVolume);
}

void voice_setReverbVolume(int amount) {

  currentVoiceReverbVolume = amount;
  float remappedAmount = (float)map(amount, 0, 100, 0, 100) / 100.0;
  Serial.print("Setting voice reverb volume to ");
  Serial.println(remappedAmount);
  mixer2.gain(0, remappedAmount);
}

void voice_lowerPitch() {

  currentVoicePitch -= 10;
  if (currentVoicePitch < 0)
    currentVoicePitch = 0;

  Serial.print("lowering voice pitch to ");
  Serial.println(currentVoicePitch);

  voice_setPitch(currentVoicePitch);
}

void voice_raisePitch() {

  currentVoicePitch += 10;
  if (currentVoicePitch > 100)
    currentVoicePitch = 100;

  Serial.print("raising voice pitch to ");
  Serial.println(currentVoicePitch);

  voice_setPitch(currentVoicePitch);
}

void voice_setPitch(int frequency) {

  currentVoicePitch = frequency;
  float remappedAmount = (float)map(frequency, 0, 100, 1, 10) / 10.0;
  Serial.print("Setting voice pitch to ");
  Serial.println(remappedAmount);
  float grainSpeed = remappedAmount; // ( 0.1 - 1.0 )
  granular1.beginPitchShift(25.0 + (grainSpeed * 75.0));
  float speedRatio = remappedAmount; // 0.5 to 2.0
  granular1.setSpeed(powf(2.0, speedRatio * 2.0 - 1.0));
}

