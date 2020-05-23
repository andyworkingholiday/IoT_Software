#include <FreeRTOS_AVR.h>
#define MS2TICKS(ms) (ms / portTICK_PERIOD_MS)

const int MT_P = 10;
const int MT_N = 9;
const int LeftKey = 2;
const int StopKey = 3;
const int RightKey = 21;

SemaphoreHandle_t Sem;
int SendValue = 0;

void LeftKeyControl() {
  delay(50);
  SendValue = 1;
  xSemaphoreGive(Sem);
}

void StopKeyControl() {
  delay(50);
  SendValue = 2;
  xSemaphoreGive(Sem);
}

void RightKeyControl() {
  delay(50);
  SendValue = 3;
  xSemaphoreGive(Sem);
}

void MotorTask(void* arg) {
  int receiveValue = 0;
  while(1) {
    if(xSemaphoreTake(Sem, portMAX_DELAY)) {
      receiveValue = SendValue;
      if(receiveValue == 1) {
        digitalWrite(MT_P, LOW);
        digitalWrite(MT_N, HIGH);
      }

      //Stop
      else if(receiveValue == 2) {
        digitalWrite(MT_P, LOW);
        digitalWrite(MT_N, LOW);
      }

      //right
      else if(receiveValue == 3) {
        digitalWrite(MT_P, HIGH);
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

  attachInterrupt(0, LeftKeyControl, RISING);
  attachInterrupt(1, StopKeyControl, RISING);
  attachInterrupt(2, RightKeyControl, RISING);
  vSemaphoreCreateBinary(Sem);

  xTaskCreate(MotorTask, NULL, 200, NULL, 1, NULL);
  vTaskStartScheduler();
}

void loop() {
  
}
