unsigned char led_on = 0b00001000;
unsigned char led_off = 0b00000000;

void setup() {
  DDRB=0b01111000;
  // PB3~PB6을 LED제어 비트로 사용
}

void loop() {
  if(led_on == 0b10000000) led_on = 0b0001000;
  PORTB = led_on;
  delay(500);
  PORTB = led_off;
  delay(500);
  led_on = led_on << 1;
  //비트 쉬프트
}
