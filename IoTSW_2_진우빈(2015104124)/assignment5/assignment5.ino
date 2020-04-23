void setup() {
  DDRB = 0b10000000;
}

void loop() {
  PORTB = 0b10000000;
  delay(1000);
  PORTB = 0b00000000;
  delay(1000);
}
