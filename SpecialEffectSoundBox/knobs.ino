#define MAX_KNOB_VALUE  1024 //65535
#define MIN_KNOB_VALUE  0

void knobs_init() {

  Serial.print("Kobs init...");
  pinMode(POTENTIOMETER_PIN_1, INPUT);
  pinMode(POTENTIOMETER_PIN_2, INPUT);
  pinMode(POTENTIOMETER_PIN_3, INPUT);
  pinMode(POTENTIOMETER_PIN_4, INPUT);
  Serial.println("done");
}

int knobs_read1() {

  tempVal = analogRead(POTENTIOMETER_PIN_1);
  return map(
    tempVal, 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}

int knobs_read2() {

  tempVal = analogRead(POTENTIOMETER_PIN_2);
  return map(
    tempVal, 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}

int knobs_read3() {

  tempVal = analogRead(POTENTIOMETER_PIN_3);
  return map(
    tempVal, 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}

int knobs_read4() {

  tempVal = analogRead(POTENTIOMETER_PIN_4);
  return map(
    tempVal, 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}
