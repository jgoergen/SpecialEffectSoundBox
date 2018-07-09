

void knobs_init() {

}

int knobs_read1() {

  return analogRead(POTENTIOMETER_PIN_1);
}

int knobs_read2() {

  return analogRead(POTENTIOMETER_PIN_2);
}

int knobs_read3() {

  return analogRead(POTENTIOMETER_PIN_3);
}

int knobs_read4() {

  return analogRead(POTENTIOMETER_PIN_4);
}
