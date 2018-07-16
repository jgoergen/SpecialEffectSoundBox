#include <Audio.h> // https://www.pjrc.com/teensy/gui/index.html?info=AudioPlaySdWav
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// DEFAULT SETTINGS //////////////////////////////////////
#define DEFAULT_KNOB_UPDATE_WAIT  10;
#define DEFAULT_BUTTON_UPDATE_WAIT  20;
#define DEFAULT_VOICE_VOLUME  80;
#define DEFAULT_VOICE_DELAY  20;
#define DEFAULT_VOICE_REVERB  20;
#define DEFAULT_VOICE_PITCH  50;
#define DEFAULT_WAVE_LAYER_1_VOLUME 80;
#define DEFAULT_WAVE_LAYER_2_VOLUME 80;
#define DEFAULT_WAVE_LAYER_3_VOLUME 80;

// PIN DEFINITIONS ///////////////////////////////////////
#define MICROPHONE_PIN  A2

#define BUTTON_PIN_1 24
#define BUTTON_PIN_2 27
#define BUTTON_PIN_3 30
#define BUTTON_PIN_4 12
#define BUTTON_PIN_5 25
#define BUTTON_PIN_6 28
#define BUTTON_PIN_7 31
#define BUTTON_PIN_8 11
#define BUTTON_PIN_9 26
#define BUTTON_PIN_10 29
#define BUTTON_PIN_11 32
#define BUTTON_PIN_12 10

#define LED_PIN_1 6
#define LED_PIN_2 2
#define LED_PIN_3 3
#define LED_PIN_4 4
#define LED_PIN_5 5

#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

// INSTANTIATIONS //////////////////////////////////////////

File configFile;

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=202.00000381469727,178.00000286102295
AudioPlaySdWav           playSdWav3;     //xy=202,447
AudioPlaySdWav           playSdWav2;     //xy=205,388
AudioPlaySdWav           playSdWav1;     //xy=206,322
AudioEffectGranular      granular1;      //xy=385.00000762939453,192.00000381469727
AudioEffectReverb        reverb1;        //xy=560,130
AudioMixer4              mixer1;         //xy=756,374
AudioMixer4              mixer2;         //xy=757,195
AudioOutputAnalog        dac1;           //xy=905,374
AudioConnection          patchCord1(adc1, granular1);
AudioConnection          patchCord2(playSdWav3, 0, mixer1, 3);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord4(playSdWav1, 0, mixer1, 1);
AudioConnection          patchCord5(granular1, reverb1);
AudioConnection          patchCord6(granular1, 0, mixer2, 1);
AudioConnection          patchCord7(reverb1, 0, mixer2, 0);
AudioConnection          patchCord8(mixer1, dac1);
AudioConnection          patchCord9(mixer2, 0, mixer1, 0);
// GUItool: end automatically generated code

// VARIABLES /////////////////////////////////////

int tempVal = 0;
int waveLayer1Volume = DEFAULT_WAVE_LAYER_1_VOLUME;
int waveLayer2Volume = DEFAULT_WAVE_LAYER_2_VOLUME;
int waveLayer3Volume = DEFAULT_WAVE_LAYER_3_VOLUME;
int voiceVolume = DEFAULT_VOICE_VOLUME;
int voicePitch = DEFAULT_VOICE_PITCH;
int voiceReverbVolume = DEFAULT_VOICE_DELAY;
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
int button9LastState = 0;
int button10LastState = 0;
int button11LastState = 0;
int button12LastState = 0;
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
  pinMode(LED_PIN_5, OUTPUT);
  Serial.println("done");

  Serial.print("Initializing SD card...");

  if (!SD.begin(BUILTIN_SDCARD)) {
    
    Serial.println("failed!");
    return;
  }
  Serial.println("done");

  config_load();
  buttons_init();
  knobs_init();

  Serial.print("Initializing audio system...");
  AudioMemory(8);
  voice_init();
  waveplayer_init();
  Serial.println("done");

  introSequence();
}

void introSequence() {
  
  digitalWrite(LED_PIN_1, 1);
  delay(100);
  digitalWrite(LED_PIN_1, 0);
  digitalWrite(LED_PIN_2, 1);
  delay(100);
  digitalWrite(LED_PIN_2, 0);
  digitalWrite(LED_PIN_3, 1);
  delay(100);
  digitalWrite(LED_PIN_3, 0);
  digitalWrite(LED_PIN_4, 1);
  delay(100);
  digitalWrite(LED_PIN_4, 0);
  digitalWrite(LED_PIN_5, 1);
  delay(100);
  digitalWrite(LED_PIN_5, 0);
  digitalWrite(LED_PIN_1, 1);
}

void loop() {

  buttons_update();
  
  if (millis() > nextKnobUpdate) {

    nextKnobUpdate = millis() + knobUpdateWait;
    //checkKnobs();
  }

  if (millis() > nextButtonUpdate) {

    nextButtonUpdate = millis() + buttonUpdateWait;
    checkButtons();
  }

  delay(10);
}

void changeMode() {

  mode ++;
  if (mode > 4)
    mode = 0;

  Serial.print("Changing mode to ");
  Serial.println(mode);

  digitalWrite(LED_PIN_1, mode == 0 ? 1 : 0);
  digitalWrite(LED_PIN_2, mode == 1 ? 1 : 0);
  digitalWrite(LED_PIN_3, mode == 2 ? 1 : 0);
  digitalWrite(LED_PIN_4, mode == 3 ? 1 : 0);
  digitalWrite(LED_PIN_5, mode == 4 ? 1 : 0);
  
  waveplayer_changeWaveSet(mode);
}

void checkButtons() {

  tempVal = buttons_read1();
  if (tempVal != button1LastState) {

    button1LastState = tempVal;
    Serial.print("Button 1 state ");
    Serial.println(button1LastState);
    
    //if (button1LastState)
    //  waveplayer_playLayer1(1);
  }

  tempVal = buttons_read2();
  if (tempVal != button2LastState) {

    button2LastState = tempVal;
    Serial.print("Button 2 state ");
    Serial.println(button2LastState);
    
    //if (button2LastState)
    //  waveplayer_playLayer2(1);
  }

  tempVal = buttons_read3();
  if (tempVal != button3LastState) {

    button3LastState = tempVal;
    Serial.print("Button 3 state ");
    Serial.println(button3LastState);
    
    //if (button3LastState)
    //  waveplayer_playLayer3(1);
  }

  tempVal = buttons_read4();
  if (tempVal != button4LastState) {

    button4LastState = tempVal;
    Serial.print("Button 4 state ");
    Serial.println(button4LastState);
    
    //if (button4LastState)
    //  changeMode();
  }

  tempVal = buttons_read5();
  if (tempVal != button5LastState) {

    button5LastState = tempVal;
    Serial.print("Button 5 state ");
    Serial.println(button5LastState);
    
    //if (button5LastState)
    //  waveplayer_playLayer1(2);
  }

  tempVal = buttons_read6();
  if (tempVal != button6LastState) {

    button6LastState = tempVal;
    Serial.print("Button 6 state ");
    Serial.println(button6LastState);
    
    //if (button6LastState)
    //  waveplayer_playLayer2(2);
  }

  tempVal = buttons_read7();
  if (tempVal != button7LastState) {

    button7LastState = tempVal;
    Serial.print("Button 7 state ");
    Serial.println(button7LastState);
    
    //if (button7LastState)
    //  waveplayer_playLayer3(2);
  }

  tempVal = buttons_read8();
  if (tempVal != button8LastState) {

    button8LastState = tempVal;
    Serial.print("Button 8 state ");
    Serial.println(button8LastState);
    /*
    if (button8LastState) {
      
      if (buttons_read4()) {

        Serial.println("Buttons 8 and 4 pressed, saving config defaults");
        
        config_save();
        digitalWrite(LED_PIN_1, 1);
        digitalWrite(LED_PIN_2, 1);
        digitalWrite(LED_PIN_3, 1);
        digitalWrite(LED_PIN_4, 1);
        digitalWrite(LED_PIN_5, 1);
        delay(2000);
        digitalWrite(LED_PIN_1, mode == 0 ? 1 : 0);
        digitalWrite(LED_PIN_2, mode == 1 ? 1 : 0);
        digitalWrite(LED_PIN_3, mode == 2 ? 1 : 0);
        digitalWrite(LED_PIN_4, mode == 3 ? 1 : 0);
        digitalWrite(LED_PIN_5, mode == 3 ? 1 : 0);
      }
      
      waveplayer_stopAllSounds();
    }*/
  }

  tempVal = buttons_read9();
  if (tempVal != button9LastState) {

    button9LastState = tempVal;
    Serial.print("Button 9 state ");
    Serial.println(button9LastState);
    
    //if (button7LastState)
    //  waveplayer_playLayer3(2);
  }

  tempVal = buttons_read10();
  if (tempVal != button10LastState) {

    button10LastState = tempVal;
    Serial.print("Button 10 state ");
    Serial.println(button10LastState);
    
    //if (button7LastState)
    //  waveplayer_playLayer3(2);
  }

  tempVal = buttons_read11();
  if (tempVal != button11LastState) {

    button11LastState = tempVal;
    Serial.print("Button 11 state ");
    Serial.println(button11LastState);
    
    //if (button7LastState)
    //  waveplayer_playLayer3(2);
  }

  tempVal = buttons_read12();
  if (tempVal != button12LastState) {

    button12LastState = tempVal;
    Serial.print("Button 12 state ");
    Serial.println(button12LastState);
    
    //if (button7LastState)
    //  waveplayer_playLayer3(2);
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
      //voice_setVolume(voiceVolume);
    }
    
  } else {

    tempVal = knobs_read1();
    if (tempVal != voicePitch) {
  
      voicePitch = tempVal;
      voice_setPitch(voicePitch);
    }
  
    tempVal = knobs_read2();
    if (tempVal != voiceReverbVolume) {
  
      voiceReverbVolume = tempVal;
      voice_setReverbVolume(voiceReverbVolume);
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
