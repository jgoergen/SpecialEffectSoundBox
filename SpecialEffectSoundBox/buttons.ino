
Bounce buttonBouncer1 = Bounce(BUTTON_PIN_1, 5); // 5 millisecond debounce time
Bounce buttonBouncer2 = Bounce(BUTTON_PIN_2, 5); // 5 millisecond debounce time
Bounce buttonBouncer3 = Bounce(BUTTON_PIN_3, 5); // 5 millisecond debounce time
Bounce buttonBouncer4 = Bounce(BUTTON_PIN_4, 5); // 5 millisecond debounce time
Bounce buttonBouncer5 = Bounce(BUTTON_PIN_5, 5); // 5 millisecond debounce time
Bounce buttonBouncer6 = Bounce(BUTTON_PIN_6, 5); // 5 millisecond debounce time
Bounce buttonBouncer7 = Bounce(BUTTON_PIN_7, 5); // 5 millisecond debounce time
Bounce buttonBouncer8 = Bounce(BUTTON_PIN_8, 5); // 5 millisecond debounce time
Bounce buttonBouncer9 = Bounce(BUTTON_PIN_9, 5); // 5 millisecond debounce time
Bounce buttonBouncer10 = Bounce(BUTTON_PIN_10, 5); // 5 millisecond debounce time
Bounce buttonBouncer11 = Bounce(BUTTON_PIN_11, 5); // 5 millisecond debounce time
Bounce buttonBouncer12 = Bounce(BUTTON_PIN_12, 5); // 5 millisecond debounce time

void buttons_init() {

  Serial.print("Buttons init...");
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(BUTTON_PIN_3, INPUT);
  pinMode(BUTTON_PIN_4, INPUT);
  pinMode(BUTTON_PIN_5, INPUT);
  pinMode(BUTTON_PIN_6, INPUT);
  pinMode(BUTTON_PIN_7, INPUT);
  pinMode(BUTTON_PIN_8, INPUT);
  pinMode(BUTTON_PIN_9, INPUT);
  pinMode(BUTTON_PIN_10, INPUT);
  pinMode(BUTTON_PIN_11, INPUT);
  pinMode(BUTTON_PIN_12, INPUT);
  Serial.println("done");
}

void buttons_update() {

  buttonBouncer1.update();
  buttonBouncer2.update();
  buttonBouncer3.update();
  buttonBouncer4.update();
  buttonBouncer5.update();
  buttonBouncer6.update();
  buttonBouncer7.update();
  buttonBouncer8.update();
  buttonBouncer9.update();
  buttonBouncer10.update();
  buttonBouncer11.update();
  buttonBouncer12.update();
}

int buttons_read1() {

  return buttonBouncer1.read();
}

int buttons_read2() {

  return buttonBouncer2.read();
}

int buttons_read3() {

  return buttonBouncer3.read();
}

int buttons_read4() {

  return buttonBouncer4.read();
}

int buttons_read5() {

  return buttonBouncer5.read();
}

int buttons_read6() {

  return buttonBouncer6.read();
}

int buttons_read7() {

  return buttonBouncer7.read();
}

int buttons_read8() {

  return buttonBouncer8.read();
}

int buttons_read9() {

  return buttonBouncer9.read();
}

int buttons_read10() {

  return buttonBouncer10.read();
}

int buttons_read11() {

  return buttonBouncer11.read();
}

int buttons_read12() {

  return buttonBouncer12.read();
}
