#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

const int FndSelectPin[6]={4,17,18,27,22,23};
const int FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[5]={0x3F, 0x38, 0x38, 0x79, 0x76};

//00111000
//01111001
//01110110

void Init() {
	int i;
	if(wiringPiSetupGpio()==-1) {
		printf("wiringPiSetupGpio()error\n");
		exit(-1);
	}

	for(i=0; i<6; i++) {
		pinMode(FndSelectPin[i], OUTPUT);
		digitalWrite(FndSelectPin[i], HIGH);
	}

	for(i=0; i<8; i++) {
		pinMode(FndPin[i], OUTPUT);
		digitalWrite(FndPin[i], LOW);
	}
}

void FndSelect(int position) {
	int i;
	for(i=0; i<6; i++) {
		if(i==position) 
			digitalWrite(FndSelectPin[i], LOW);
		else 
			digitalWrite(FndSelectPin[i], HIGH);
	}
}

void FndDisplay(int position, int num) {
	int i;
	int flag = 0;
	int shift = 0x01;

	for(i=0; i<8; i++) {
		flag=(FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift<<=1;
	}

	FndSelect(position);
}

int main() {
	Init();
	
	int i, pos, delaysum;
	while(1) {
		for(i=0; i<6; i++) {
			delaysum=0;
			while(delaysum<500) {
				for(pos=0; pos<5; pos++) {
					FndDisplay((pos+i)%6,pos);
					delay(1);
				}
				delaysum+=5;
			}
			
		}			
		
	}

	return 0;

}

// 00 11 22 33 44
// 10 21 32 43 54
// 20 31 42 53 64
// 30 41 52 63 74

	