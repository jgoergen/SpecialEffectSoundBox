#define MAX_KNOB_VALUE  0
#define MIN_KNOB_VALUE  100

void knobs_init() {

}

int knobs_read1() {

  return map(
    analogRead(POTENTIOMETER_PIN_1), 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}

int knobs_read2() {

  return map(
    analogRead(POTENTIOMETER_PIN_2), 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}

int knobs_read3() {

  return map(
    analogRead(POTENTIOMETER_PIN_3), 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}

int knobs_read4() {

  return map(
    analogRead(POTENTIOMETER_PIN_4), 
    MIN_KNOB_VALUE, 
    MAX_KNOB_VALUE, 
    0, 
    100);
}
