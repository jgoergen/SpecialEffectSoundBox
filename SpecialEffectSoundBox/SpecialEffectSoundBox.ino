#include <Audio.h> // https://www.pjrc.com/teensy/gui/index.html?info=AudioPlaySdWav
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

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

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=74,29
AudioInputAnalog         adc1;           //xy=76,82
AudioPlaySdWav           playSdWav3;     //xy=85,325
AudioPlaySdWav           playSdWav2;     //xy=88,266
AudioPlaySdWav           playSdWav1;     //xy=89,200
AudioEffectMultiply      multiply1;      //xy=217,51
AudioEffectReverb        reverb1;        //xy=355,52
AudioEffectDelay         delay1;         //xy=495,98
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
AudioConnection          patchCord8(delay1, 0, mixer2, 0);
AudioConnection          patchCord9(delay1, 1, mixer2, 1);
AudioConnection          patchCord10(delay1, 2, mixer2, 2);
AudioConnection          patchCord11(delay1, 3, mixer2, 3);
AudioConnection          patchCord12(mixer1, dac1);
AudioConnection          patchCord13(mixer2, 0, mixer1, 0);
// GUItool: end automatically generated code

int overallVolume = 80;
int waveLayer1Volume = 80;
int waveLayer2Volume = 80;
int waveLayer3Volume = 80;
int mode = 0;

void setup() {
  
  // put your setup code here, to run once:

}

void loop() {

  int tempVal = 0;

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
}
