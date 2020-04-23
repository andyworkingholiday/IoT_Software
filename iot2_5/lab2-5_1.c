#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_NPIN 17
#define MOTOR_PPIN 4

#define LEFT 1
#define RIGHT 2

void MotorStop() {
	softPwmWrite(MOTOR_NPIN, 0);
	softPwmWrite(MOTOR_PPIN, 0);
}

void MotorControl(int rotate) {
	if(rotate==LEFT) {
		digitalWrite(MOTOR_PPIN, LOW);
		softPwmWrite(MOTOR_NPIN, 50);
	}

	else if(rotate==RIGHT) {
		digitalWrite(MOTOR_NPIN, LOW);
		softPwmWrite(MOTOR_PPIN, 50);
	}
}

int main(void) {
	if(wiringPiSetupGpio()==-1) return 1;

	pinMode(MOTOR_NPIN, OUTPUT);
	pinMode(MOTOR_PPIN, OUTPUT);

	softPwmCreate(MOTOR_NPIN, 0, 100);
	softPwmCreate(MOTOR_PPIN, 0, 100);

	while(1) {

		MotorControl(LEFT);
		delay(2000);
		MotorStop();
		delay(1000);

		MotorControl(RIGHT);
		delay(2000);
		MotorStop();
		delay(1000);
	}
	
	return 0;
}