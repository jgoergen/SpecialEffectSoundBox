// playSdWav1 Layer1_x.wav
// playSdWav2 Layer2_x.wav
// playSdWav3 Layer3_x.wav

int currentLayer1Sound = 0;
int currentLayer2Sound = 0;
int currentLayer3Sound = 0;

void waveplayer_init() {
  
}

void waveplayer_changeWaveSet(int setNumber) {
  
}

void waveplayer_playLayer1(int soundNumber) {

  if (soundNumber == currentLayer1Sound) {

    playSdWav1.stop();
    currentLayer1Sound = 0;
  }

  switch (soundNumber) {
    
    case 1:
      playSdWav1.play("Layer1_1.wav");
      currentLayer1Sound = 1;
      break;
      
    case 2:
      playSdWav1.play("Layer1_2.wav");
      currentLayer1Sound = 2;
      break;
  }
}

void waveplayer_setLayer1Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */
  
  mixer1.gain(1, 0);
}


void waveplayer_playLayer2(int soundNumber) {

  if (soundNumber == currentLayer2Sound) {

    playSdWav2.stop();
    currentLayer2Sound = 0;
  }
  
  switch (soundNumber) {
    
    case 1:
      playSdWav2.play("Layer2_1.wav");
      currentLayer2Sound = 1;
      break;
      
    case 2:
      playSdWav2.play("Layer2_2.wav");
      currentLayer2Sound = 2;
      break;
  }
}

void waveplayer_setLayer2Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */
  
  mixer1.gain(2, 0);
}

void waveplayer_playLayer3(int soundNumber) {

  if (soundNumber == currentLayer3Sound) {

    playSdWav3.stop();
    currentLayer3Sound = 0;
  }
  
  switch (soundNumber) {
    
    case 1:
      playSdWav3.play("Layer3_1.wav");
      currentLayer3Sound = 1;
      break;
      
    case 2:
      playSdWav3.play("Layer3_2.wav");
      currentLayer3Sound = 2;
      break;
  }
}

void waveplayer_setLayer3Volume(int volume) {

  /*
  any floating point number from 0 to 32767.0. 1.0 passes the signal through directly. 
  Level of 0 shuts the channel off completely. Between 0 to 1.0 attenuates the signal, and above 1.0 amplifies it
  */
  
  mixer1.gain(3, 0);
}

void waveplayer_stopAllSounds() {

  playSdWav1.stop();
  currentLayer1Sound = 0;
  playSdWav2.stop();
  currentLayer2Sound = 0;
  playSdWav3.stop();
  currentLayer3Sound = 0;
}

