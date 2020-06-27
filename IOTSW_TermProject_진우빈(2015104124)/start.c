#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wiringPi.h>

#define FIFO_FILE	"/tmp/fifo"
#define BUFF_SIZE	1024

const int FndSelectPin[6]={4,7,18,27,22,23};
const int FndPin[8] = {6,12,13,16,19,20,26,21};
const int FndDigit[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
const int FndDigit2[10] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xE7};

int timer = 0;
bool stop = false;

void Setup() {
	int i;

	if(wiringPiSetupGpio() == -1) {
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

	stop = false;
}

void FndSelect(int pos) {
	int i;

	for(i=0; i<6; i++) {
		if(i==pos)
			digitalWrite(FndSelectPin[i], LOW);
		else	
			digitalWrite(FndSelectPin[i], HIGH);
	}
}

void FndDisplay(int pos, int num) {
	int i;
	int flag = 0;
	int shift = 0x01;

	FndSelect(pos);
	
	if(pos==2) {
		for(i=0; i<8; i++) {
			flag = (FndDigit2[num] & shift);
			digitalWrite(FndPin[i], flag);
			shift <<= 1;
		}
	}

	else {
		for(i=0; i<8; i++) {
			flag = (FndDigit[num] & shift);
			digitalWrite(FndPin[i], flag);
			shift <<= 1;
		}
	}
}


void FndThread(void* arg) {
	while(1) {
		int i;
		int data[10]={0,1,2,3,4,5,6,7,8,9};

		for(i=0; i<6; i++) {
			FndDisplay(i, data[(timer/(int)pow(10,i))%10]);
			delay(1);
			if((i+timer)%2 == 0)
				delay(1);
		}

		delay(1);

		if(stop) 
			continue;

		timer++;

		if(timer>=1000000) {
			timer = 0;
		}
	}
}


void IPCThread(void* arg) {
	int fd;
	char buff[BUFF_SIZE];

	if(-1 == mkfifo(FIFO_FILE, 0666)) {
		perror("mkfifo() error!");
		exit(1);
	}

	
	if(-1 == (fd = open(FIFO_FILE, O_RDWR))) {
		perror("open() error!");
		exit(1);
	}

	while(1) {
		memset(buff, 0, BUFF_SIZE);

		read(fd, buff, BUFF_SIZE);
		if(buff=="stop") {
			stop = true;
		}

		else if(buff=="clear") {
			timer = 0;
		}

		else {
			perror("read buff error!");
			exit(1);
		}
	}
}


int main() {
	printf("Content-type:text/html\n\n");
	printf("<html>\n<head>\n<title>STOP WATCH!</title>\n</head>\n");
	printf("<body>\n<p>Start</p>\n");

	int pid;
	pid = fork();
	if(pid > 0) {
		Setup();
	}

	else if(pid == 0) {

		pthread_t p_thread[2];
		int thr_id;
		int status;
		int a = 1;
		int b = 2;

		thr_id = pthread_create(&p_thread[0], NULL, FndThread, (void *)&a);

		if(thr_id < 0) {
			perror("thread create error: ");
			exit(1);
		}

		thr_id = pthread_create(&p_thread[1], NULL, IPCThread, (void *)&b);

		if(thr_id <0) {
			perror("thread create error: ");
			exit(1);
		}

		pthread_join(p_thread[0], (void **)&status);
		pthread_join(p_thread[1], (void **)&status);

	}

	else if(pid == -1) {
		perror("fork error: ");
		exit(1);
	}

	printf("</body>\n</html>");

	return 0;
}
