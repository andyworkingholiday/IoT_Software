enum{REST=0, DO=262, RE=294, MI=330, FA=349, SOL=392, LA=440, SHI=404, DO2=523};
#define BUZZER 9
#define LED 5
int NUM=9;
int Frequency[]={DO,MI,REST,FA,SOL,LA,LA,DO2};

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  for(int i=0; i<8; i++) {
    tone(BUZZER, Frequency[i]);
    if(i%2==0) digitalWrite(LED, HIGH);
    else digitalWrite(LED, LOW);
    delay(500);
  }
}
