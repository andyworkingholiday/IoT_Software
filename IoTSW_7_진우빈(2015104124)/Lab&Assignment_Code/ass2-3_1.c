#include <wiringPi.h>
const int LedRed[8]={4,17,18,27,22,23,24,25};
const int Keypad[8]={16,13,12,6,21,26,20,19};

void Button1() {
	static int output1= HIGH;	
	digitalWrite(LedRed[0], output1);
	output1 = (output1+1)%2;
}

void Button2() {
	static int output2= HIGH;	
	digitalWrite(LedRed[1], output2);
	output2 = (output2+1)%2;
}

void Button3() {
	static int output3= HIGH;	
	digitalWrite(LedRed[2], output3);
	output3 = (output3+1)%2;
}

void Button4() {
	static int output4= HIGH;	
	digitalWrite(LedRed[3], output4);
	output4 = (output4+1)%2;
}
void Button5() {
	static int output5= HIGH;	
	digitalWrite(LedRed[4], output5);
	output5 = (output5+1)%2;
}
void Button6() {
	static int output6= HIGH;	
	digitalWrite(LedRed[5], output6);
	output6 = (output6+1)%2;
}
void Button7() {
	static int output7= HIGH;	
	digitalWrite(LedRed[6], output7);
	output7 = (output7+1)%2;
}

void Button8() {
	static int output8= HIGH;	
	digitalWrite(LedRed[7], output8);
	output8 = (output8+1)%2;
}

int main(void) {
	int i,keypadnum = -1;
	if(wiringPiSetupGpio()==-1) return 1;

	for(i=0; i<8; i++) {
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
		pinMode(Keypad[i], INPUT);
	}

	if(wiringPiISR(Keypad[0], INT_EDGE_RISING, Button1)<0) return 1;
	if(wiringPiISR(Keypad[1], INT_EDGE_RISING, Button2)<0) return 1;
	if(wiringPiISR(Keypad[2], INT_EDGE_RISING, Button3)<0) return 1;
	if(wiringPiISR(Keypad[3], INT_EDGE_RISING, Button4)<0) return 1;
	if(wiringPiISR(Keypad[4], INT_EDGE_RISING, Button5)<0) return 1;
	if(wiringPiISR(Keypad[5], INT_EDGE_RISING, Button6)<0) return 1;
	if(wiringPiISR(Keypad[6], INT_EDGE_RISING, Button7)<0) return 1;
	if(wiringPiISR(Keypad[7], INT_EDGE_RISING, Button8)<0) return 1;

	while(1) {

	}

	return 0;
}
