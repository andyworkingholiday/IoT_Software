#include <MsTimer2.h>

int Button[2] = {2,3};
int Led[3]={5,6,7};
int ledState = HIGH;
int buttonState1;
int buttonState2;
int lastButtonState1= LOW;
int lastButtonState2= HIGH;

void LedControl() {
  static int counter = 0;
  static byte output = HIGH;

  digitalWrite(Led[counter++], output);
  if(counter > 1) {
    counter = 0;
    output = !output;
  }
}


void setup() {
  pinMode(Button[0], INPUT_PULLUP);
  pinMode(Button[1], INPUT_PULLUP);
  for (int i=0; i<3; i++) pinMode(Led[i], OUTPUT);
  MsTimer2::set(500, LedControl);
  MsTimer2::start();
}

void loop() {
  int reading1 = digitalRead(Button[0]);
  int reading2 = digitalRead(Button[1]);

  if(reading1 != buttonState1) {
    buttonState1 = reading1;
    if(buttonState1 == HIGH) {
      ledState = !ledState;
    }

    digitalWrite(Led[2], ledState);
    lastButtonState1 = reading1;
  }

  else if(reading2 != buttonState2) {
    buttonState2 = reading2;
    if(buttonState2 == LOW) {
      ledState = !ledState;
    }

    digitalWrite(Led[2], ledState);
    lastButtonState2 = reading2;
  }

}
