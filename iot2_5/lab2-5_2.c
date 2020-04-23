#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_NPIN 17
#define MOTOR_PPIN 4

void MotorStop() {
	softPwmWrite(MOTOR_NPIN, 0);
	softPwmWrite(MOTOR_PPIN, 0);
}

void MotorControl(int speed) {
	digitalWrite(MOTOR_PPIN, LOW);
	softPwmWrite(MOTOR_NPIN, speed);
}

int main(void) {
	if(wiringPiSetupGpio()==-1) return 1;

	pinMode(MOTOR_NPIN, OUTPUT);
	pinMode(MOTOR_PPIN, OUTPUT);

	softPwmCreate(MOTOR_NPIN, 0, 100);
	softPwmCreate(MOTOR_PPIN, 0, 100);

	while(1) {

		MotorControl(25);
		delay(2000);
		MotorStop();
		delay(2000);

		MotorControl(50);
		delay(2000);
		MotorStop();
		delay(2000);

		MotorControl(75);
		delay(2000);
		MotorStop();
		delay(2000);
	}
	
	return 0;
}