// playSdWav1 Layer1_x.wav
// playSdWav2 Layer2_x.wav
// playSdWav3 Layer3_x.wav

int currentLayer1Sound = 0;
int currentLayer2Sound = 0;
int currentLayer3Sound = 0;
int currentWaveSet = 0;

void waveplayer_init() {

  Serial.println("Waveplayer...");
}

void waveplayer_changeWaveSet(int setNumber) {

  Serial.print("Changing waveSet to ");
  Serial.println(setNumber);
  waveplayer_stopAllSounds();
  currentWaveSet = setNumber;
}

void waveplayer_playLayer1(int soundNumber) {

  if (soundNumber == currentLayer1Sound) {

    Serial.println("Stopping Layer 1");
    playSdWav1.stop();
    currentLayer1Sound = 0;
  }

  switch (soundNumber) {
    
    case 1:
      Serial.println("Playing Layer 1 Sound 1");
      
      if (currentWaveSet == 0)
        playSdWav1.play("m1l1s1.wav");
      else if (currentWaveSet == 1)
        playSdWav1.play("m2l1s1.wav");
      else if (currentWaveSet == 2)
        playSdWav1.play("m3l1s1.wav");
      else if (currentWaveSet == 3)
        playSdWav1.play("m4l1s1.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer1Sound = 1;
      break;
      
    case 2:

      Serial.println("Playing Layer 1 Sound 2");
      
      if (currentWaveSet == 0)
        playSdWav1.play("m1l1s2.wav");
      else if (currentWaveSet == 1)
        playSdWav1.play("m2l1s2.wav");
      else if (currentWaveSet == 2)
        playSdWav1.play("m3l1s2.wav");
      else if (currentWaveSet == 3)
        playSdWav1.play("m4l1s2.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer1Sound = 2;
      break;
  }
}

void waveplayer_setLayer1Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */
  
  float remappedAmount = (float)map(volume, 0, 100, 0, 400) / 100.0;
  Serial.print("Setting Layer 1 volume to ");
  Serial.println(remappedAmount);
  mixer1.gain(1, remappedAmount);
}


void waveplayer_playLayer2(int soundNumber) {

  if (soundNumber == currentLayer2Sound) {

    Serial.println("Stopping Layer 2");
    playSdWav2.stop();
    currentLayer2Sound = 0;
  }
  
  switch (soundNumber) {
    
    case 1:

      Serial.println("Playing Layer 2 sound 1");
      
      if (currentWaveSet == 0)
        playSdWav1.play("m1l2s1.wav");
      else if (currentWaveSet == 1)
        playSdWav1.play("m2l2s1.wav");
      else if (currentWaveSet == 2)
        playSdWav1.play("m3l2s1.wav");
      else if (currentWaveSet == 3)
        playSdWav1.play("m4l2s1.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer2Sound = 1;
      break;
      
    case 2:

      Serial.println("Playing Layer 2 sound 2");
      
      if (currentWaveSet == 0)
        playSdWav1.play("m1l2s2.wav");
      else if (currentWaveSet == 1)
        playSdWav1.play("m2l2s2.wav");
      else if (currentWaveSet == 2)
        playSdWav1.play("m3l2s2.wav");
      else if (currentWaveSet == 3)
        playSdWav1.play("m4l2s2.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer2Sound = 2;
      break;
  }
}

void waveplayer_setLayer2Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */
  
  float remappedAmount = (float)map(volume, 0, 100, 0, 400) / 100.0;
  Serial.print("Setting Layer 2 volume to ");
  Serial.println(remappedAmount);
  mixer1.gain(2, remappedAmount);
}

void waveplayer_playLayer3(int soundNumber) {

  if (soundNumber == currentLayer3Sound) {

    Serial.println("Stopping Layer 3");
    playSdWav3.stop();
    currentLayer3Sound = 0;
  }
  
  switch (soundNumber) {
    
    case 1:

      Serial.println("Playing Layer 3 sound 1");
      
      if (currentWaveSet == 0)
        playSdWav1.play("m1l3s1.wav");
      else if (currentWaveSet == 1)
        playSdWav1.play("m2l3s1.wav");
      else if (currentWaveSet == 2)
        playSdWav1.play("m3l3s1.wav");
      else if (currentWaveSet == 3)
        playSdWav1.play("m4l3s1.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer3Sound = 1;
      break;
      
    case 2:

      Serial.println("Playing Layer 3 sound 2");
      
      if (currentWaveSet == 0)
        playSdWav1.play("m1l3s2.wav");
      else if (currentWaveSet == 1)
        playSdWav1.play("m2l3s2.wav");
      else if (currentWaveSet == 2)
        playSdWav1.play("m3l3s2.wav");
      else if (currentWaveSet == 3)
        playSdWav1.play("m4l3s2.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer3Sound = 2;
      break;
  }
}

void waveplayer_setLayer3Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */

  float remappedAmount = (float)map(volume, 0, 100, 0, 400) / 100.0;
  Serial.print("Setting Layer 3 volume to ");
  Serial.println(remappedAmount);
  mixer1.gain(3, remappedAmount);
}

void waveplayer_stopAllSounds() {

  Serial.println("Stopping all layers");
  playSdWav1.stop();
  currentLayer1Sound = 0;
  playSdWav2.stop();
  currentLayer2Sound = 0;
  playSdWav3.stop();
  currentLayer3Sound = 0;
}

