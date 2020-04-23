#define BUZZER 5
#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define B 494
#define C1 523
#define four 250
#define two 500

void samenotebreak(int note) {
  tone(BUZZER, note);
  delay(four-30);
  noTone(BUZZER);
  delay(30);
}

void sizetwo(int note) {
  tone(BUZZER, note);
  delay(two);
}



void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
 samenotebreak(G);
 samenotebreak(G);
 samenotebreak(A);
 samenotebreak(A);
 samenotebreak(G);
 samenotebreak(G);
 sizetwo(E);
 samenotebreak(G);
 samenotebreak(G);
 samenotebreak(E);
 samenotebreak(E);
 sizetwo(D);
 tone(BUZZER, D);
 delay(four);
 noTone(BUZZER);
 delay(four);

 samenotebreak(G);
 samenotebreak(G);
 samenotebreak(A);
 samenotebreak(A);
 samenotebreak(G);
 samenotebreak(G);
 sizetwo(E);
 tone(BUZZER, G);
 delay(four);
 tone(BUZZER, E);
 delay(four);
 tone(BUZZER, D);
 delay(four);
 tone(BUZZER, E);
 delay(four);

 sizetwo(C);
 tone(BUZZER, C);
 delay(four);
 noTone(BUZZER);
 delay(four);
 delay(two);
}
