int Led[4]={5, 6, 7, 8};

void setup() {
  for (int i=0; i<4; i++) {
    pinMode(Led[i], OUTPUT);
  }
}

void loop() {
  for (int i=0; i<2; i++) {
    digitalWrite(Led[i*2], HIGH);
    digitalWrite(Led[i*2+1], HIGH);
    delay(500);
    digitalWrite(Led[i*2], LOW);
    digitalWrite(Led[i*2+1], LOW);
    delay(500);
  }

}
