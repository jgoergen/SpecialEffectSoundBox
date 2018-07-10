#include <Audio.h> // https://www.pjrc.com/teensy/gui/index.html?info=AudioPlaySdWav
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// DEFAULT SETTINGS //////////////////////////////////////
#define DEFAULT_KNOB_UPDATE_WAIT  0;
#define DEFAULT_BUTTON_UPDATE_WAIT  100;
#define DEFAULT_VOICE_VOLUME  80;
#define DEFAULT_VOICE_DELAY  20;
#define DEFAULT_VOICE_REVERB  20;
#define DEFAULT_VOICE_PITCH  50;
#define DEFAULT_WAVE_LAYER_1_VOLUME 80;
#define DEFAULT_WAVE_LAYER_2_VOLUME 80;
#define DEFAULT_WAVE_LAYER_3_VOLUME 80;

// PIN DEFINITIONS ///////////////////////////////////////
#define POTENTIOMETER_PIN_1 1
#define POTENTIOMETER_PIN_2 1
#define POTENTIOMETER_PIN_3 1
#define POTENTIOMETER_PIN_4 1

#define BUTTON_PIN_1 1
#define BUTTON_PIN_2 1
#define BUTTON_PIN_3 1
#define BUTTON_PIN_4 1
#define BUTTON_PIN_5 1
#define BUTTON_PIN_6 1
#define BUTTON_PIN_7 1
#define BUTTON_PIN_8 1

#define LED_PIN_1 1
#define LED_PIN_2 1
#define LED_PIN_3 1
#define LED_PIN_4 1

#define SD_CHIP_SELECT = BUILTIN_SDCARD;

// INSTANTIATIONS //////////////////////////////////////////

File configFile;

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=74,29
AudioInputAnalog         adc1;           //xy=76,82
AudioPlaySdWav           playSdWav3;     //xy=85,325
AudioPlaySdWav           playSdWav2;     //xy=88,266
AudioPlaySdWav           playSdWav1;     //xy=89,200
AudioEffectMultiply      multiply1;      //xy=217,51
AudioEffectReverb        reverb1;        //xy=355,52
AudioEffectDelay         delay1;         //xy=501,129
AudioMixer4              mixer1;         //xy=639,252
AudioMixer4              mixer2;         //xy=640,73
AudioOutputAnalog        dac1;           //xy=788,252
AudioConnection          patchCord1(sine1, 0, multiply1, 0);
AudioConnection          patchCord2(adc1, 0, multiply1, 1);
AudioConnection          patchCord3(playSdWav3, 0, mixer1, 3);
AudioConnection          patchCord4(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord5(playSdWav1, 0, mixer1, 1);
AudioConnection          patchCord6(multiply1, reverb1);
AudioConnection          patchCord7(reverb1, delay1);
AudioConnection          patchCord8(reverb1, 0, mixer2, 0);
AudioConnection          patchCord9(delay1, 0, mixer2, 1);
AudioConnection          patchCord10(delay1, 1, mixer2, 2);
AudioConnection          patchCord11(delay1, 2, mixer2, 3);
AudioConnection          patchCord12(mixer1, dac1);
AudioConnection          patchCord13(mixer2, 0, mixer1, 0);
// GUItool: end automatically generated code

// VARIABLES /////////////////////////////////////

int tempVal = 0;
int waveLayer1Volume = DEFAULT_WAVE_LAYER_1_VOLUME;
int waveLayer2Volume = DEFAULT_WAVE_LAYER_2_VOLUME;
int waveLayer3Volume = DEFAULT_WAVE_LAYER_3_VOLUME;
int voiceVolume = DEFAULT_VOICE_VOLUME;
int voicePitch = DEFAULT_VOICE_PITCH;
int voiceDelay = DEFAULT_VOICE_DELAY;
int voiceReverb = DEFAULT_VOICE_REVERB;
int mode = 0;
int button1LastState = 0;
int button2LastState = 0;
int button3LastState = 0;
int button4LastState = 0;
int button5LastState = 0;
int button6LastState = 0;
int button7LastState = 0;
int button8LastState = 0;
int knobUpdateWait = DEFAULT_KNOB_UPDATE_WAIT;
int buttonUpdateWait = DEFAULT_BUTTON_UPDATE_WAIT;
unsigned long nextKnobUpdate = 0; 
unsigned long nextButtonUpdate = 0;

// MAIN CODE ///////////////////////////////////////

void setup() {

  Serial.begin(9600);

  Serial.print("Initializing LED pins...");
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  Serial.println("done");

  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_CHIP_SELECT)) {
    
    Serial.println("failed!");
    return;
  }
  Serial.println("done");

  config_load();  
}

void loop() {

  if (millis() - nextKnobUpdate > knobUpdateWait) {

    nextKnobUpdate = millis() + knobUpdateWait;
    checkKnobs();
  }

  if (millis() - nextButtonUpdate > buttonUpdateWait) {

    nextButtonUpdate = millis() + buttonUpdateWait;
    checkButtons();
  }  
}

void changeMode() {

  mode ++;
  if (mode > 3)
    mode = 0;

  digitalWrite(LED_PIN_1, mode == 0 ? 1 : 0);
  digitalWrite(LED_PIN_2, mode == 1 ? 1 : 0);
  digitalWrite(LED_PIN_3, mode == 2 ? 1 : 0);
  digitalWrite(LED_PIN_4, mode == 3 ? 1 : 0);
  
  waveplayer_changeWaveSet(mode);
}

void checkButtons() {

  tempVal = buttons_read1();
  if (tempVal != button1LastState) {

    button1LastSate = tempVal;
    waveplayer_playLayer1(1);
  }

  tempVal = buttons_read2();
  if (tempVal != button2LastState) {

    button2LastSate = tempVal;
    waveplayer_playLayer2(1);
  }

  tempVal = buttons_read3();
  if (tempVal != button3LastState) {

    button3LastSate = tempVal;
    waveplayer_playLayer3(1);
  }

  tempVal = buttons_read4();
  if (tempVal != button4LastState) {

    button4LastSate = tempVal;
    changeMode();
  }

  tempVal = buttons_read5();
  if (tempVal != button5LastState) {

    button5LastSate = tempVal;
    waveplayer_playLayer1(2);
  }

  tempVal = buttons_read6();
  if (tempVal != button6LastState) {

    button6LastSate = tempVal;
    waveplayer_playLayer2(2);
  }

  tempVal = buttons_read7();
  if (tempVal != button7LastState) {

    button7LastSate = tempVal;
    waveplayer_playLayer3(2);
  }

  tempVal = buttons_read8();
  if (tempVal != button8LastState) {

    button8LastSate = tempVal;
    waveplayer_stopAllSounds();
  }

  if (buttons_read4() && buttons_read8()) {

    config_save();
    digitalWrite(LED_PIN_1, 1);
    digitalWrite(LED_PIN_2, 1);
    digitalWrite(LED_PIN_3, 1);
    digitalWrite(LED_PIN_4, 1);
    delay(2000);
    digitalWrite(LED_PIN_1, mode == 0 ? 1 : 0);
    digitalWrite(LED_PIN_2, mode == 1 ? 1 : 0);
    digitalWrite(LED_PIN_3, mode == 2 ? 1 : 0);
    digitalWrite(LED_PIN_4, mode == 3 ? 1 : 0);
  }
}

void checkKnobs() {

  // if Stop All is being held down, the knobs change sound channel levels
  if (buttons_read8()) {
      
    tempVal = knobs_read1();
    if (tempVal != waveLayer1Volume) {
  
      waveLayer1Volume = tempVal;
      waveplayer_setLayer1Volume(waveLayer1Volume);
    }
  
    tempVal = knobs_read2();
    if (tempVal != waveLayer2Volume) {
  
      waveLayer2Volume = tempVal;
      waveplayer_setLayer2Volume(waveLayer2Volume);
    }
  
    tempVal = knobs_read3();
    if (tempVal != waveLayer3Volume) {
  
      waveLayer3Volume = tempVal;
      waveplayer_setLayer3Volume(waveLayer3Volume);
    }
  
    tempVal = knobs_read4();
    if (tempVal != voiceVolume) {
  
      voiceVolume = tempVal;
      voice_setVolume(voiceVolume);
    }
    
  } else {

    tempVal = knobs_read1();
    if (tempVal != voicePitch) {
  
      voicePitch = tempVal;
      voice_setPitch(voicePitch);
    }
  
    tempVal = knobs_read2();
    if (tempVal != voiceDelay) {
  
      voiceDelay = tempVal;
      voice_setDelay(voiceDelay);
    }
  
    tempVal = knobs_read3();
    if (tempVal != voiceReverb) {
  
      voiceReverb = tempVal;
      voice_setReverb(voiceReverb);
    }
  
    tempVal = knobs_read4();
    if (tempVal != voiceVolume) {
  
      voiceVolume = tempVal;
      voice_setVolume(voiceVolume);
    }
  }
}
