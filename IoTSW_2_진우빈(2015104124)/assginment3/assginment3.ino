int Led[4]={5, 6, 7, 8};
int delaytime = 500;

void setup() {
  for (int i=0; i<4; i++) {
    pinMode(Led[i], OUTPUT);
  }
}

void loop() {
  if(delaytime == 2500) delaytime = 500;
  for (int i=0; i<4; i++) {
    digitalWrite(Led[i], HIGH);
    delay(delaytime);
    digitalWrite(Led[i], LOW);
    delay(delaytime);
    }    
    delaytime+=500;
}
