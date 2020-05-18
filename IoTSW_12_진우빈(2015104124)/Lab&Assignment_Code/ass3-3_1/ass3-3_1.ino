#include <FreeRTOS_AVR.h>

const int MT_P = 10;
const int MT_N = 9;

// 아두이노 인터럽트 핀번호0~4에 해당하는 번호로 설정
const int LeftKey = 2;
const int StopKey = 3;
const int RightKey = 21;
const int LeftAcc = 20;
const int RightAcc = 19;

// 25% Duty Cycle 정의 64로 할 시 전원이 부족해서 인지 모터가 제대로 돌아가지 않아서 70으로 설정
// 50%, 75%, 100% 순서대로의 Duty Cycle 값
const int Duty25 = 85;
const int DutyCycle[3]={127,191,255};
int CycleNumLeft = -1;
int CycleNumRight = -1;

QueueHandle_t xQueue;

void LeftKeyControl() {
  uint16_t sendValue = 1;
  xQueueSendFromISR(xQueue, &sendValue,0);
}

void StopKeyControl() {
  uint16_t sendValue = 2;
  xQueueSendFromISR(xQueue, &sendValue,0);
}

void RightKeyControl() {
  uint16_t sendValue = 3;
  xQueueSendFromISR(xQueue, &sendValue,0);
}

void LeftKeyAccelerate() {
  uint16_t sendValue = 4;
  xQueueSendFromISR(xQueue, &sendValue,0);
}

void RightKeyAccelerate() {
  uint16_t sendValue = 5;
  xQueueSendFromISR(xQueue, &sendValue,0);
}


void MotorTask(void* arg) {
  uint16_t receiveValue = 0;

  while(1) {
    if(xQueueReceive(xQueue, &receiveValue,0)) {
      //left rotate
      if(receiveValue == 1) {
        CycleNumLeft = -1;
        CycleNumRight = -1;
        digitalWrite(MT_P, LOW);
        analogWrite(MT_N, Duty25);
      }

      //Stop
      else if(receiveValue == 2) {
        CycleNumLeft = -1;
        CycleNumRight = -1;
        digitalWrite(MT_P, LOW);
        digitalWrite(MT_N, LOW);
      }

      //right rotate
      else if(receiveValue == 3) {
        CycleNumLeft = -1;
        CycleNumRight = -1;
        analogWrite(MT_P, Duty25);
        digitalWrite(MT_N, LOW);
      }

      //left Accelerate
      else if(receiveValue == 4) {
        CycleNumRight = -1;
        CycleNumLeft=(CycleNumLeft+1)%3;
        digitalWrite(MT_P, LOW);
        analogWrite(MT_N, DutyCycle[CycleNumLeft]);
      }

      //right Accelerate
      else if(receiveValue == 5) {
        CycleNumLeft = -1;
        CycleNumRight=(CycleNumRight+1)%3;
        analogWrite(MT_P, DutyCycle[CycleNumRight]);
        digitalWrite(MT_N, LOW);
      }
    }
  }
}

void setup() {
  pinMode(MT_P, OUTPUT);
  pinMode(MT_N, OUTPUT);
  pinMode(LeftKey, INPUT);
  pinMode(StopKey, INPUT);
  pinMode(RightKey, INPUT);
  pinMode(LeftAcc, INPUT);
  pinMode(RightAcc, INPUT);

  attachInterrupt(0, LeftKeyControl, RISING);
  attachInterrupt(1, StopKeyControl, RISING);
  attachInterrupt(2, RightKeyControl, RISING);
  attachInterrupt(3, LeftKeyAccelerate, RISING);
  attachInterrupt(4, RightKeyAccelerate, RISING);

  xQueue = xQueueCreate(5, sizeof(uint16_t));

  if(xQueue != NULL) {
    xTaskCreate(MotorTask, NULL, 200, NULL, 1, NULL);
    vTaskStartScheduler();
  }
}

void loop() {
  
}
