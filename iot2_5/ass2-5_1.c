#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_NPIN 17
#define MOTOR_PPIN 4
#define WIDTH 32

#define LEFT 1
#define RIGHT 2

void MotorStop() {
	softPwmWrite(MOTOR_NPIN, 0);
	softPwmWrite(MOTOR_PPIN, 0);
}

void MotorControl(int rotate, int speed) {
	if(rotate==LEFT) {
		digitalWrite(MOTOR_PPIN, LOW);
		softPwmWrite(MOTOR_NPIN, speed);
	}

	else if(rotate==RIGHT) {
		digitalWrite(MOTOR_NPIN, LOW);
		softPwmWrite(MOTOR_PPIN, speed);
	}
}

int main(void) {
	if(wiringPiSetupGpio()==-1) return 1;

	pinMode(MOTOR_NPIN, OUTPUT);
	pinMode(MOTOR_PPIN, OUTPUT);

	softPwmCreate(MOTOR_NPIN, 0, 128);
	softPwmCreate(MOTOR_PPIN, 0, 128);

	while(1) {
		int s = WIDTH;
		int i;

		for(i=0; i<4; i++) {
			MotorControl(LEFT, s);
			delay(2000);
			MotorStop();
			delay(2000);
			s+=WIDTH;
		}

		s = WIDTH;
	
		for(i=0; i<4; i++) {
			MotorControl(RIGHT, s);
			delay(2000);
			MotorStop();
			delay(2000);
			s+=WIDTH;
		}
	}
	
	return 0;
}