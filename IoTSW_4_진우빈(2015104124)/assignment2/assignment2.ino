#define BUZZER 5
#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define B 494
#define C1 523
#define eight 125
#define four 250
#define two 500

void samenotebreak(int note, int leng) {
  tone(BUZZER, note);
  delay(leng-float(leng/10));
  noTone(BUZZER);
  delay(float(leng/10));
}

void note(int note, int leng) {
  tone(BUZZER, note);
  delay(leng);
}

void rest(int leng) {
  noTone(BUZZER);
  delay(leng);
}

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop(){
  samenotebreak(C, four);
  samenotebreak(C, eight);
  samenotebreak(C, eight);
  samenotebreak(C, four);
  samenotebreak(C, four);
  note(E, four);
  samenotebreak(G, eight);
  samenotebreak(G, eight);
  note(E, four);
  note(C, four);

  samenotebreak(G, eight);
  samenotebreak(G, eight);
  note(E, four);
  samenotebreak(G, eight);
  samenotebreak(G, eight);
  note(E, four);
  samenotebreak(C, four);
  samenotebreak(C, four);
  samenotebreak(C, two);

  samenotebreak(G, four);
  samenotebreak(G, four);
  note(E, four);
  note(C, four);
  samenotebreak(G, four);
  samenotebreak(G, four);
  samenotebreak(G, two);

  samenotebreak(G, four);
  samenotebreak(G, four);
  note(E, four);
  note(C, four);
  samenotebreak(G, four);
  samenotebreak(G, four);
  samenotebreak(G, two);

  samenotebreak(G, four);
  samenotebreak(G, four);
  note(E, four);
  note(C, four);
  samenotebreak(G, eight);
  samenotebreak(G, eight);
  note(G, eight);
  note(A, eight);
  note(G, two);

  note(C1, four);
  note(G, four);
  note(C1, four);
  note(G, four);
  note(E, four);
  note(D, four);
  note(C, two);
  rest(1000);
}
