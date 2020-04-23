int Led[4]={5, 6, 7, 8};

void setup() {
  for (int i=0; i<4; i++) {
    pinMode(Led[i], OUTPUT);
  }
}

void loop() {
  for (int i=0; i<4; i++) {
    digitalWrite(Led[i], HIGH);
    delay(500);
    digitalWrite(Led[i], LOW);
    delay(500);
  }

}
