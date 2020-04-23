enum{REST=0, DO=262, RE=294, MI=330, FA=349, SOL=392, LA=440, SHI=404, DO2=523};
#define BUZZER 5

int NUM=9;
int Frequency[]={DO,RE,MI,REST,FA,SOL,LA,SHI,DO2};
int Delay[]={500,0,500,500,500,500,1000,0,500};

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  for (int i=0; i<NUM; i++) {
    tone(BUZZER, Frequency[i]);
    delay(Delay[i]);
  }
}
