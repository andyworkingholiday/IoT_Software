#include <MsTimer2.h>

int Button[2] = {2,3};
int Led[3]={5,6,7};

void LedControl() {
  static int counter = 0;
  static byte output = HIGH;

  digitalWrite(Led[counter++], output);
  if(counter > 1) {
    counter = 0;
    output = !output;
  }
}

void ButtonLedOn() {
  digitalWrite(Led[2], HIGH);
}

void ButtonLedOff() {
  digitalWrite(Led[2], LOW);
}


void setup() {
  pinMode(Button[0], INPUT_PULLUP);
  pinMode(Button[1], INPUT_PULLUP);
  for (int i=0; i<3; i++) pinMode(Led[i], OUTPUT);
  attachInterrupt(1, ButtonLedOn, FALLING);
  attachInterrupt(0, ButtonLedOff, RISING);
  MsTimer2::set(500, LedControl);
  MsTimer2::start();
}

void loop() {
  
}
