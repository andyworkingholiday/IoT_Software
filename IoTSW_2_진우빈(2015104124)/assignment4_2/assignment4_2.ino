#include <MsTimer2.h>

int Led[5]={5,6,7,8,9};

void LedControl() {
  static int counter = 0;
  static byte output = HIGH;
  digitalWrite(Led[counter++],output);
  if(counter > 3) {
    counter = 0;
    output = !output;
  }
}

void setup() {
  for (int i=0; i<5; i++) {
    pinMode(Led[i], OUTPUT);
  }
  MsTimer2::set(500, LedControl);
  MsTimer2::start();
}

void loop() {
  digitalWrite(Led[4], HIGH);
  delay(1000);
  digitalWrite(Led[4], LOW);
  delay(1000);
}
