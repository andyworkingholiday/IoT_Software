#include <FreeRTOS_AVR.h>
#define MS2TICKS(ms) (ms / portTICK_PERIOD_MS)
#define N 5

const int MT_P = 10;
const int MT_N = 9;
const int LeftKey = 2;
const int StopKey = 3;
const int RightKey = 21;

// 크기 5의 CirCular Queue Structure를 만들어 줌
struct BoundedBuffer {
  int arr[N];
  int in = N - 1;
  int out = N - 1;
};

// Binary SemaPhore인 Mutex와 Empty, Full SemaPhore 정의
SemaphoreHandle_t Mutex;
SemaphoreHandle_t Empty;
SemaphoreHandle_t Full;
int SendValue = 0, keypad = 0;

// Buff라는 이름의 Circular Queue 정의
BoundedBuffer Buff;

// 인터럽트가 들어올 때 Mutex에 세마포어를 놓아서 나중에 Take할 수 있게 해줌
void LeftKeyControl() {
  delay(50);
  SendValue = 1;
  xSemaphoreGive(Mutex);
}

void StopKeyControl() {
  delay(50);
  SendValue = 2;
  xSemaphoreGive(Mutex);
}

void RightKeyControl() {
  delay(50);
  SendValue = 3;
  xSemaphoreGive(Mutex);
}

void KeypadTask(void* arg) { 
  while(1) {    
    // 인터럽트를 통해 Mutex가 1이 되면 0으로 값을 내리면서 Take, 그리고 Empty의 Semaphore 또한 값을 내리면서 Take
    // 또한 같은 값을 받은 Debouncing을 방지하기 위해 keypad와 SendValue 값을 따로 선언, 두 값이 다를 시 이후 함수 작동 
    if(xSemaphoreTake(Mutex, portMAX_DELAY) && keypad != SendValue && xSemaphoreTake(Empty, portMAX_DELAY)) {
      keypad = SendValue;
      Buff.arr[Buff.in] = keypad;
      Buff.in = (Buff.in + 1) % N; // Circular Queue에 값 대입해서 저장       
      xSemaphoreGive(Mutex); 
      xSemaphoreGive(Full); // Consumer인 MotorTask가 접근할 수 있게 Mutex 와 Full의 Semaphore를 1 더해준다.
    }    
  }
}

void MotorTask(void* arg) {
  int data;
  while(1) {

    // Producer를 통해 Full Semaphore에서 Take가 가능하면 Take하면서 Mutex의 Semaphore 또한 0으로 바뀌면서 Take
    if(xSemaphoreTake(Mutex, portMAX_DELAY) && xSemaphoreTake(Full, portMAX_DELAY)) {
      data = Buff.arr[Buff.out];
      Buff.out = (Buff.out + 1) % N; // Circular queue의 out으로 부터 값을 불러온다. 

      //Left
      if(data == 1) {
        digitalWrite(MT_P, LOW);
        digitalWrite(MT_N, HIGH);
      }

      //Stop
      else if(data == 2) {
        digitalWrite(MT_P, LOW);
        digitalWrite(MT_N, LOW);
      }

      //right
      else if(data == 3) {
        digitalWrite(MT_P, HIGH);
        digitalWrite(MT_N, LOW);
      }

      xSemaphoreGive(Mutex);
      xSemaphoreGive(Empty); // Producer인 KeypadTask가 접근할 수 있게 Mutex 와 Empty의 Semaphore를 1 더해준다.
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
  vSemaphoreCreateBinary(Mutex);
  Empty = xSemaphoreCreateCounting(5, 5);
  Full = xSemaphoreCreateCounting(5, 0);
  
  
  xTaskCreate(KeypadTask, NULL, 200, NULL, 1, NULL);
  xTaskCreate(MotorTask, NULL, 200, NULL, 2, NULL);
  vTaskStartScheduler();
}

void loop() {
  
}
