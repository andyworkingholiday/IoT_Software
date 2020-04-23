#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

const int FndSelectPin[6]={4,17,18,27,22,23};
const int FndPin[8]={6,12,13,16,19,20,26,21};
const int FndFont[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,0x7F, 0x67};
int FndFontpoint[10];


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
	if(position!=2) {
		for(i=0; i<8; i++) {
		flag=(FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift<<=1;
		}			
	}
	
	else {
		for(i=0; i<8; i++) {
		flag=(FndFontpoint[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift<<=1;	
		}
	}

	FndSelect(position);
	delay(1);
}

int main() {
	Init();
	int times, d0,d1,d2,d3,d4,d5, i;
	for(i=0; i<10; i++)
		FndFontpoint[i]=FndFont[i]+0x80;
	while(1) {
		times=millis()/10;
		
		d0 = times % 10;
		d1 = (times / 10) % 10;
		d2 = (times / 100) % 10;
		d3 = (times / 1000) % 10;
		d4 = (times / 10000) % 10;
		d5 = (times / 100000) % 10;

		FndDisplay(0,d0);
		if(times >=10) FndDisplay(1,d1);
		if(times >=100) FndDisplay(2,d2);
		if(times >=1000) FndDisplay(3,d3);
		if(times >=10000) FndDisplay(4,d4);
		if(times >=100000) FndDisplay(5,d5);
			
	}

	return 0;

}

	
