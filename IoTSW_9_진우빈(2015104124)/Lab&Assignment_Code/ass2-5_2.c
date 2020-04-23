#include <wiringPi.h>
#include <softPwm.h>

#define LED_PIN 4

const int Led[15]={17,18,27,22,23,24,25,6,12,13,16,19,20,26,21};

void LedControl(int light) {
	softPwmWrite(LED_PIN, light);
}

int main(void) {
	if(wiringPiSetupGpio()==-1) return 1;

	pinMode(LED_PIN, OUTPUT);
	softPwmCreate(LED_PIN, 0, 500);

	int i;
	for(i=0; i<15; i++) {
		digitalWrite(Led[i], LOW);
	}

	while(1) {
		
		int ledlight = 0;

		for(i=0; i<500; i++) {
			LedControl(ledlight);
			delay(5);
			ledlight+=1;	
		}

		LedControl(ledlight); // ledlight 100%
		delay(1000);

		for(i=0; i<500; i++) {
			LedControl(ledlight);
			delay(5);
			ledlight-=1;	
		}
		
		LedControl(ledlight);
		delay(1000);		
	}
	
	return 0;
}