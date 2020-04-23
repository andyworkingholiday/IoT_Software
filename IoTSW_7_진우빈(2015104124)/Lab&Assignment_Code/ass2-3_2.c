#include <wiringPi.h>
const int LedRed[8] = {4,17,18,27,22,23,24,25};
const int Keypad[3] = {16,13,12};
int keypadnum=3;
int lednum = 0;

void KeypadRead() {
	int i;
	for (i=0; i<3; i++) {
		if(!digitalRead(Keypad[i])) {
			keypadnum=i;
			break;
		}
	}
}


void LedControl(int num) {
	int i;
	for(i=0; i<8; i++) {
		if(i==num)
			digitalWrite(LedRed[i], HIGH);

		else
			digitalWrite(LedRed[i], LOW);
	}
}


int main(void) {
	int i;
	if(wiringPiSetupGpio() == -1) return 1;
	for (i=0; i<8; i++) {
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	};

	for(i=0; i<3; i++)
		pinMode(Keypad[i], INPUT);


	while(1) {
		KeypadRead();
		if(keypadnum==0) {
			if(lednum==8) lednum=0;
			LedControl(lednum);
			delay(500);
			lednum++;
		}

		else if(keypadnum==1) {
			if(lednum==-1) lednum=7;
			LedControl(lednum);
			delay(500);
			lednum--;
		}

		else if(keypadnum==2) {
			LedControl(lednum);
		}

	}

	return 0;
} 
