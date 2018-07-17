#include <Audio.h> // https://www.pjrc.com/teensy/gui/index.html?info=AudioPlaySdWav
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// DEFAULT SETTINGS //////////////////////////////////////
#define DEFAULT_BUTTON_UPDATE_WAIT  20
#define DEFAULT_VOICE_VOLUME  80
#define DEFAULT_VOICE_DELAY  20
#define DEFAULT_VOICE_REVERB  20
#define DEFAULT_VOICE_PITCH  50
#define DEFAULT_WAVE_LAYER_1_VOLUME 80
#define DEFAULT_WAVE_LAYER_2_VOLUME 80
#define DEFAULT_WAVE_LAYER_3_VOLUME 80
#define SETTING_BLINK_RATE  4

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

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=182,151
AudioPlaySdWav           playSdWav3;     //xy=182,420
AudioPlaySdWav           playSdWav2;     //xy=185,361
AudioPlaySdWav           playSdWav1;     //xy=186,295
AudioPlaySdWav           playSdWav4;     //xy=202,471
AudioEffectGranular      granular1;      //xy=365,165
AudioEffectReverb        reverb1;        //xy=540,103
AudioMixer4              mixer3;         //xy=559.0000076293945,351.0000057220459
AudioMixer4              mixer1;         //xy=736,347
AudioMixer4              mixer2;         //xy=737,168
AudioOutputAnalog        dac1;           //xy=885,347
AudioConnection          patchCord1(adc1, granular1);
AudioConnection          patchCord2(playSdWav3, 0, mixer3, 2);
AudioConnection          patchCord3(playSdWav2, 0, mixer3, 1);
AudioConnection          patchCord4(playSdWav1, 0, mixer3, 0);
AudioConnection          patchCord5(playSdWav4, 0, mixer3, 3);
AudioConnection          patchCord6(granular1, reverb1);
AudioConnection          patchCord7(granular1, 0, mixer2, 1);
AudioConnection          patchCord8(reverb1, 0, mixer2, 0);
AudioConnection          patchCord9(mixer3, 0, mixer1, 1);
AudioConnection          patchCord10(mixer1, dac1);
AudioConnection          patchCord11(mixer2, 0, mixer1, 0);
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
int buttonUpdateWait = DEFAULT_BUTTON_UPDATE_WAIT;
unsigned long nextButtonUpdate = 0;
int inputMode = 0;
int blinkSkip = 0; 
int blinkPhase = 0;

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

  buttons_init();

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

  if (millis() > nextButtonUpdate) {

    nextButtonUpdate = millis() + buttonUpdateWait;

    if (inputMode == 0)
      checkButtons();
    else if (inputMode == 1)
      checkWaveSettings();
    else if (inputMode == 2)
      checkVoiceSettings();
  }

  delay(10);
}

void changeMode() {

  mode ++;
  if (mode > 4)
    mode = 0;

  Serial.print("Changing mode to ");
  Serial.println(mode);
  updateModeLEDS();
  waveplayer_changeWaveSet(mode);
}

void updateModeLEDS() {

  digitalWrite(LED_PIN_1, mode == 0 ? 1 : 0);
  digitalWrite(LED_PIN_2, mode == 1 ? 1 : 0);
  digitalWrite(LED_PIN_3, mode == 2 ? 1 : 0);
  digitalWrite(LED_PIN_4, mode == 3 ? 1 : 0);
  digitalWrite(LED_PIN_5, mode == 4 ? 1 : 0);
}

void checkWaveSettings() {

  // blink leds
  blinkSkip++;
  if (blinkSkip > SETTING_BLINK_RATE) {

    blinkSkip = 0;
    blinkPhase ++;
    if (blinkPhase == 2)
      blinkPhase = 0;

    digitalWrite(LED_PIN_1, blinkPhase);
    digitalWrite(LED_PIN_2, blinkPhase);
  }

  tempVal = buttons_read1();
  if (tempVal != button1LastState) {

    button1LastState = tempVal;

    // sound volume adjustments
    if (button1LastState){

      Serial.println("Changing to inputMode 0");
      inputMode = 0;
      updateModeLEDS();
      return;
    }
  }

  tempVal = buttons_read2();
  if (tempVal != button2LastState) {

    button2LastState = tempVal;
    
    // voice settings
    if (button2LastState){

      Serial.println("Changing to inputMode 2");
      inputMode = 2;
      digitalWrite(LED_PIN_1, 0);
      digitalWrite(LED_PIN_2, 0);
      return;
    }
  }
  
  tempVal = buttons_read3();
  if (tempVal != button3LastState) {

    button3LastState = tempVal;
    
    if (button3LastState) {

      waveplayer_stopAllSounds();
    }
  }

  tempVal = buttons_read4();
  if (tempVal != button4LastState) {

    button4LastState = tempVal;
    
    if (button4LastState){

      changeMode();
    }
  }

  tempVal = buttons_read5();
  if (tempVal != button5LastState) {

    button5LastState = tempVal;
    
    if (button5LastState){

      waveplayer_raiseLayer1Volume();
    }
  }

  tempVal = buttons_read9();
  if (tempVal != button9LastState) {

    button9LastState = tempVal;
    
    if (button9LastState){

      waveplayer_lowerLayer1Volume();
    }
  }

  tempVal = buttons_read6();
  if (tempVal != button6LastState) {

    button6LastState = tempVal;
    
    if (button6LastState){

      waveplayer_raiseLayer2Volume();
    }
  }

  tempVal = buttons_read10();
  if (tempVal != button10LastState) {

    button10LastState = tempVal;

    if (button10LastState){

      waveplayer_lowerLayer2Volume();
    }
  }

  tempVal = buttons_read7();
  if (tempVal != button7LastState) {

    button7LastState = tempVal;
    
    if (button7LastState){

      waveplayer_raiseLayer3Volume();
    }
  }

  tempVal = buttons_read11();
  if (tempVal != button11LastState) {

    button11LastState = tempVal;
    
    if (button11LastState){

      waveplayer_lowerLayer3Volume();
    }
  }

  tempVal = buttons_read8();
  if (tempVal != button8LastState) {

    button8LastState = tempVal;
    
    if (button8LastState){

      waveplayer_raiseLayer4Volume();
    }
  }

  tempVal = buttons_read12();
  if (tempVal != button12LastState) {

    button12LastState = tempVal;
    
    if (button12LastState){

      waveplayer_lowerLayer4Volume();
    }
  }
}

void checkVoiceSettings() {

  // blink leds
  blinkSkip++;
  if (blinkSkip > SETTING_BLINK_RATE) {

    blinkSkip = 0;
    blinkPhase ++;
    if (blinkPhase == 2)
      blinkPhase = 0;

    digitalWrite(LED_PIN_4, blinkPhase);
    digitalWrite(LED_PIN_5, blinkPhase);
  }

  tempVal = buttons_read1();
  if (tempVal != button1LastState) {

    button1LastState = tempVal;

    // sound volume adjustments
    if (button1LastState){

      Serial.println("Changing to inputMode 1");
      digitalWrite(LED_PIN_4, 0);
      digitalWrite(LED_PIN_5, 0);
      inputMode = 1;
      return;
    }
  }

  tempVal = buttons_read2();
  if (tempVal != button2LastState) {

    button2LastState = tempVal;
    
    // voice settings
    if (button2LastState){

      Serial.println("Changing to inputMode 0");
      inputMode = 0;
      updateModeLEDS();
      return;
    }
  }
  
  tempVal = buttons_read3();
  if (tempVal != button3LastState) {

    button3LastState = tempVal;
    
    if (button3LastState) {

      waveplayer_stopAllSounds();
    }
  }

  tempVal = buttons_read4();
  if (tempVal != button4LastState) {

    button4LastState = tempVal;
    
    if (button4LastState){

      changeMode();
    }
  }

  tempVal = buttons_read5();
  if (tempVal != button5LastState) {

    button5LastState = tempVal;
    
    if (button5LastState){

      voice_raiseVolume();
    }
  }

  tempVal = buttons_read9();
  if (tempVal != button9LastState) {

    button9LastState = tempVal;
    
    if (button9LastState){

      voice_lowerVolume();
    }
  }

  tempVal = buttons_read6();
  if (tempVal != button6LastState) {

    button6LastState = tempVal;
    
    if (button6LastState){

      voice_raiseReverb();
    }
  }

  tempVal = buttons_read10();
  if (tempVal != button10LastState) {

    button10LastState = tempVal;

    if (button10LastState){

      voice_lowerReverb();
    }
  }

  tempVal = buttons_read7();
  if (tempVal != button7LastState) {

    button7LastState = tempVal;
    
    if (button7LastState){

      voice_raiseReverbVolume();
    }
  }

  tempVal = buttons_read11();
  if (tempVal != button11LastState) {

    button11LastState = tempVal;
    
    if (button11LastState){

      voice_lowerReverbVolume();
    }
  }

  tempVal = buttons_read8();
  if (tempVal != button8LastState) {

    button8LastState = tempVal;
    
    if (button8LastState){

      voice_raisePitch();
    }
  }

  tempVal = buttons_read12();
  if (tempVal != button12LastState) {

    button12LastState = tempVal;
    
    if (button12LastState){

      voice_lowerPitch();
    }
  }
}

void checkButtons() {

  tempVal = buttons_read1();
  if (tempVal != button1LastState) {

    button1LastState = tempVal;

    // sound volume adjustments
    if (button1LastState){

      Serial.println("Changing to inputMode 1");
      inputMode = 1;
      return;
    }
  }

  tempVal = buttons_read2();
  if (tempVal != button2LastState) {

    button2LastState = tempVal;
    
    // voice settings
    if (button2LastState){

      Serial.println("Changing to inputMode 2");
      inputMode = 2;
      return;
    }
  }

  tempVal = buttons_read3();
  if (tempVal != button3LastState) {

    button3LastState = tempVal;
    
    if (button3LastState) {

      waveplayer_stopAllSounds();
    }
  }

  tempVal = buttons_read4();
  if (tempVal != button4LastState) {

    button4LastState = tempVal;
    
    if (button4LastState){

      changeMode();
    }
  }

  tempVal = buttons_read5();
  if (tempVal != button5LastState) {

    button5LastState = tempVal;
    
    if (button5LastState){

      waveplayer_playLayer1(1);
    }
  }

  tempVal = buttons_read6();
  if (tempVal != button6LastState) {

    button6LastState = tempVal;
    
    if (button6LastState){

      waveplayer_playLayer2(1);
    }
  }

  tempVal = buttons_read7();
  if (tempVal != button7LastState) {

    button7LastState = tempVal;
    
    if (button7LastState){

      waveplayer_playLayer3(1);
    }
  }

  tempVal = buttons_read8();
  if (tempVal != button8LastState) {

    button8LastState = tempVal;

    if (button8LastState){

      waveplayer_playLayer4(1);
    }
  }

  tempVal = buttons_read9();
  if (tempVal != button9LastState) {

    button9LastState = tempVal;
    
    if (button9LastState){

      waveplayer_playLayer1(2);
    }
  }

  tempVal = buttons_read10();
  if (tempVal != button10LastState) {

    button10LastState = tempVal;
    
    if (button10LastState){

      waveplayer_playLayer2(2);
    }
  }

  tempVal = buttons_read11();
  if (tempVal != button11LastState) {

    button11LastState = tempVal;
    
    if (button11LastState){

      waveplayer_playLayer3(2);
    }
  }

  tempVal = buttons_read12();
  if (tempVal != button12LastState) {

    button12LastState = tempVal;
    
    if (button12LastState){

      waveplayer_playLayer4(2);
    }
  }
}
