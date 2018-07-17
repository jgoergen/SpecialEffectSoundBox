// playSdWav1 Layer1_x.wav
// playSdWav2 Layer2_x.wav
// playSdWav3 Layer3_x.wav

int currentLayer1Sound = 0;
int currentLayer2Sound = 0;
int currentLayer3Sound = 0;
int currentLayer4Sound = 0;
int currentLayer1Volume = 30;
int currentLayer2Volume = 30;
int currentLayer3Volume = 30;
int currentLayer4Volume = 30;
int currentWaveSet = 0;

void waveplayer_init() {

  Serial.println("Waveplayer...");
  waveplayer_setLayer1Volume(currentLayer1Volume);
  waveplayer_setLayer2Volume(currentLayer2Volume);
  waveplayer_setLayer3Volume(currentLayer3Volume);
  waveplayer_setLayer4Volume(currentLayer4Volume);
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
      else if (currentWaveSet == 4)
        playSdWav1.play("m5l1s1.wav");

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
      else if (currentWaveSet == 4)
        playSdWav1.play("m5l1s2.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer1Sound = 2;
      break;
  }
}

void waveplayer_lowerLayer1Volume() {

  currentLayer1Volume -= 10;
  if (currentLayer1Volume < 0)
    currentLayer1Volume = 0;

  Serial.print("lowering layer 1 volume to ");
  Serial.println(currentLayer1Volume);
  
  waveplayer_setLayer1Volume(currentLayer1Volume);
}

void waveplayer_raiseLayer1Volume() {

  currentLayer1Volume += 10;
  if (currentLayer1Volume > 100)
    currentLayer1Volume = 100;

  Serial.print("raising layer 1 volume to ");
  Serial.println(currentLayer1Volume);

  waveplayer_setLayer1Volume(currentLayer1Volume);
}

void waveplayer_setLayer1Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */

  currentLayer1Volume = volume;
  float remappedAmount = (float)map(volume, 0, 100, 0, 200) / 100.0;
  Serial.print("Setting Layer 1 volume to ");
  Serial.println(remappedAmount);
  mixer3.gain(0, remappedAmount);
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
        playSdWav2.play("m1l2s1.wav");
      else if (currentWaveSet == 1)
        playSdWav2.play("m2l2s1.wav");
      else if (currentWaveSet == 2)
        playSdWav2.play("m3l2s1.wav");
      else if (currentWaveSet == 3)
        playSdWav2.play("m4l2s1.wav");
      else if (currentWaveSet == 4)
        playSdWav2.play("m5l2s1.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer2Sound = 1;
      break;
      
    case 2:

      Serial.println("Playing Layer 2 sound 2");
      
      if (currentWaveSet == 0)
        playSdWav2.play("m1l2s2.wav");
      else if (currentWaveSet == 1)
        playSdWav2.play("m2l2s2.wav");
      else if (currentWaveSet == 2)
        playSdWav2.play("m3l2s2.wav");
      else if (currentWaveSet == 3)
        playSdWav2.play("m4l2s2.wav");
      else if (currentWaveSet == 4)
        playSdWav2.play("m5l2s2.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer2Sound = 2;
      break;
  }
}

void waveplayer_lowerLayer2Volume() {

  currentLayer2Volume -= 10;
  if (currentLayer2Volume < 0)
    currentLayer2Volume = 0;

  Serial.print("lowering layer 2 volume to ");
  Serial.println(currentLayer2Volume);

  waveplayer_setLayer2Volume(currentLayer2Volume);
}

void waveplayer_raiseLayer2Volume() {

  currentLayer2Volume += 10;
  if (currentLayer2Volume > 100)
    currentLayer2Volume = 100;

  Serial.print("raising layer 2 volume to ");
  Serial.println(currentLayer2Volume);

  waveplayer_setLayer2Volume(currentLayer2Volume);
}

void waveplayer_setLayer2Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */

  currentLayer2Volume = volume;
  float remappedAmount = (float)map(volume, 0, 100, 0, 200) / 100.0;
  Serial.print("Setting Layer 2 volume to ");
  Serial.println(remappedAmount);
  mixer3.gain(1, remappedAmount);
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
        playSdWav3.play("m1l3s1.wav");
      else if (currentWaveSet == 1)
        playSdWav3.play("m2l3s1.wav");
      else if (currentWaveSet == 2)
        playSdWav3.play("m3l3s1.wav");
      else if (currentWaveSet == 3)
        playSdWav3.play("m4l3s1.wav");
      else if (currentWaveSet == 4)
        playSdWav3.play("m5l3s1.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer3Sound = 1;
      break;
      
    case 2:

      Serial.println("Playing Layer 3 sound 2");
      
      if (currentWaveSet == 0)
        playSdWav3.play("m1l3s2.wav");
      else if (currentWaveSet == 1)
        playSdWav3.play("m2l3s2.wav");
      else if (currentWaveSet == 2)
        playSdWav3.play("m3l3s2.wav");
      else if (currentWaveSet == 3)
        playSdWav3.play("m4l3s2.wav");
      else if (currentWaveSet == 4)
        playSdWav3.play("m5l3s2.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer3Sound = 2;
      break;
  }
}

void waveplayer_lowerLayer3Volume() {

  currentLayer3Volume -= 10;
  if (currentLayer3Volume < 0)
    currentLayer3Volume = 0;

  Serial.print("lowering layer 3 volume to ");
  Serial.println(currentLayer3Volume);
  
  waveplayer_setLayer3Volume(currentLayer3Volume);
}

void waveplayer_raiseLayer3Volume() {

  currentLayer3Volume += 10;
  if (currentLayer3Volume > 100)
    currentLayer3Volume = 100;

  Serial.print("raising layer 3 volume to ");
  Serial.println(currentLayer3Volume);
  
  waveplayer_setLayer3Volume(currentLayer3Volume);
}

void waveplayer_setLayer3Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */

  currentLayer3Volume = volume;
  float remappedAmount = (float)map(volume, 0, 100, 0, 200) / 100.0;
  Serial.print("Setting Layer 3 volume to ");
  Serial.println(remappedAmount);
  mixer3.gain(2, remappedAmount);
}

void waveplayer_playLayer4(int soundNumber) {

  if (soundNumber == currentLayer3Sound) {

    Serial.println("Stopping Layer 4");
    playSdWav4.stop();
    currentLayer4Sound = 0;
  }
  
  switch (soundNumber) {
    
    case 1:

      Serial.println("Playing Layer 4 sound 1");
      
      if (currentWaveSet == 0)
        playSdWav4.play("m1l4s1.wav");
      else if (currentWaveSet == 1)
        playSdWav4.play("m2l4s1.wav");
      else if (currentWaveSet == 2)
        playSdWav4.play("m3l4s1.wav");
      else if (currentWaveSet == 3)
        playSdWav4.play("m4l4s1.wav");
      else if (currentWaveSet == 4)
        playSdWav4.play("m5l4s1.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer4Sound = 1;
      break;
      
    case 2:

      Serial.println("Playing Layer 4 sound 2");
      
      if (currentWaveSet == 0)
        playSdWav4.play("m1l4s2.wav");
      else if (currentWaveSet == 1)
        playSdWav4.play("m2l4s2.wav");
      else if (currentWaveSet == 2)
        playSdWav4.play("m3l4s2.wav");
      else if (currentWaveSet == 3)
        playSdWav4.play("m4l4s2.wav");
      else if (currentWaveSet == 4)
        playSdWav4.play("m5l4s2.wav");

      delay(10); // wait for library to parse WAV info
      currentLayer4Sound = 2;
      break;
  }
}

void waveplayer_lowerLayer4Volume() {

  currentLayer4Volume -= 10;
  if (currentLayer4Volume < 0)
    currentLayer4Volume = 0;

  Serial.print("lowering layer 4 volume to ");
  Serial.println(currentLayer4Volume);

  waveplayer_setLayer4Volume(currentLayer4Volume);
}

void waveplayer_raiseLayer4Volume() {

  currentLayer4Volume += 10;
  if (currentLayer4Volume > 100)
    currentLayer4Volume = 100;

  Serial.print("raising layer 4 volume to ");
  Serial.println(currentLayer4Volume);

  waveplayer_setLayer4Volume(currentLayer4Volume);
}

void waveplayer_setLayer4Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */

  currentLayer4Volume = volume;
  float remappedAmount = (float)map(volume, 0, 100, 0, 200) / 100.0;
  Serial.print("Setting Layer 4 volume to ");
  Serial.println(remappedAmount);
  mixer3.gain(3, remappedAmount);
}

void waveplayer_stopAllSounds() {

  Serial.println("Stopping all layers");
  playSdWav1.stop();
  currentLayer1Sound = 0;
  playSdWav2.stop();
  currentLayer2Sound = 0;
  playSdWav3.stop();
  currentLayer3Sound = 0;
  playSdWav4.stop();
  currentLayer4Sound = 0;
}

