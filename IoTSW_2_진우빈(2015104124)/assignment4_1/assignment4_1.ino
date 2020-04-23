int Led[5]={5, 6, 7, 8, 9};

void setup() {
  for (int i=0; i<5; i++) {
    pinMode(Led[i], OUTPUT);
  }
}

void loop() {
  for (int i=0; i<4; i++) {
    if(i%2==0) {
      digitalWrite(Led[4], HIGH);
    }

    else if(i%2==1) {
      digitalWrite(Led[4], LOW);
    }
    
    digitalWrite(Led[i], HIGH); 
    delay(500);
    digitalWrite(Led[i], LOW);
    delay(500);
  }
}
