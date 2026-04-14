#include "tasks.h"
#include "taskStats.h"

#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "oop_chprintf.h"

// Enters a critical section, runs code, then leaves (ensures lock/unlock pairs)
#define CRITICAL_SECTION(x) do { \
  chSysLock();        \
  x                   \
  chSysUnlock();      \
} while (0);

TaskState taskBState = { 0 };
TaskState taskCBState = { 0 };
TaskState taskMState = { 0 };
TaskState taskSState = { 0 };
TaskState taskCState = { 0 };
TaskState taskFState = { 0 };

TaskStats taskStats[6] = {{ 0 }};

// Blink built-in LED at a frequency
void taskB(void) {
  // In ms
  static int blinkDuration = 1000;
  // Time between release and dedline
  static int maxDelay = 100;

  while (1) {
    // Start Task
    palToggleLine(LINE_LED_GREEN);
    msg_t msg;
    if(chMBFetchI(&taskBInbox, &msg) == MSG_OK){
      blinkDuration = (int)msg;
    }
    // End Task
    
    updateTaskState(&taskBState, blinkDuration, maxDelay);
    // Wait until next release
    chThdSleepUntil(taskBState.nextWake);
  }
}

// Set the frequency of taskB using IPC
void taskCB(void) {
  // In ms
  static int changeDelay = 10000;
  // Time between release and deadline
  static int maxDelay = 100;
  static int durations[10] = {
    1000, 750, 500, 250, 100, 50, 150, 400, 700, 1500
  };
  static int durationIndex = 0;

  while(1) {
    // Start Task
    durationIndex = (durationIndex+1)%10;
    chMBPostI(&taskBInbox, (msg_t)durations[durationIndex]);
    // End Task
    
    updateTaskState(&taskCBState, changeDelay, maxDelay);
    // Wait until next release
    chThdSleepUntil(taskCBState.nextWake);
  }
}

// Monitor all other tasks for period, duration, average actual duration, and failure/rejection counts
void taskM(void) {
  // Period should be lower than any other period, except task F since its malicious
  static int period = 100;
  static int maxDelay = 75;
  
  TaskState *taskStates[6] = {
    &taskBState, &taskCBState, &taskMState, &taskSState, &taskCState, &taskFState
  };

  
  while(1) {
    // Start task
    chMtxLock(&taskStatsMutex);
    for(int i=0;i<6;++i){
      reviewTask(&taskStats[i], taskStates[i]);
    }
    chMtxUnlock(&taskStatsMutex);
    // End task
    updateTaskState(&taskMState, period, maxDelay);
    // Wait until next release
    chThdSleepUntil(taskMState.nextWake);
  }
}

// Send taskM data over Serial using IPC, non-preemptable
void taskS(void) {
  const char* msg = "\r\nThread Statistics:\r\n\n";

  const char* taskNames[6] = {
    "taskB", "TaskCB", "taskM", "taskS", "taskC", "taskF"
  };

  static int period = 2000;
  static int maxDelay = 1000;
  
  while(1) {
    CRITICAL_SECTION(
      sdWriteTimeout(&SD2, (const uint8_t *)msg, strlen(msg), TIME_MS2I(1));

      chMtxLock(&taskStatsMutex);
      for (int i = 0; i < 6; ++i) {
        TaskStats *stats = &taskStats[i];
        uint32_t period = stats->period;
        uint32_t duration = stats->duration;
        uint32_t failureCount = stats-> failureCount;

        chprintf((sequential_stream_i *)&SD2,
                 "%s:\r\n\tperiod: %lu\r\n\tduration: %lu\r\n\tfailures: %lu\r\n",
                 taskNames[i], period, duration, failureCount);
      }
      chMtxUnlock(&taskStatsMutex);
    )
    updateTaskState(&taskSState, period, maxDelay);
    // Wait until next release
    chThdSleepUntil(taskSState.nextWake);
  }
}

// Compute math operations provided by Serial, non-preemptable
void taskC(void) {
  while(1){
    char buff[64] = { 0 };
    // Wait for serial input
    buff[0] = sdGet(&SD2);
    taskCState.nextWake = chVTGetSystemTime();
    taskCState.nextDeadline = chTimeAddX(taskCState.nextWake, TIME_MS2I(5000));
    CRITICAL_SECTION(
      sdRead(&SD2, &buff[1], 63);
    )
    int index = 0;
    int a = 0;
    int b = 0;
    char op;
    int res;
    uint_fast8_t abort = 0;
    while(abort == 0 && '0' <= buff[index] && buff[index] <= '9'){
      a*=10;
      a+= buff[index++]-'0';
      if(index >= 63){
        abort = 1;
      }
    }
    if(abort == 0){
      op = buff[index++];
    }
    while(abort == 0 && '0' <= buff[index] && buff[index] <= '9'){
      b*=10;
      b+= buff[index++]-'0';
      if(index >= 64){
        abort = 1;
      }
    }
    switch(op){
      case '+':{
        res = a+b;
      }break;
      case '-':{
        res = a-b;
      }break;
      case '*':{
        res = a*b;
      }break;
      case '/':{
        res = a/b;
      }break;
      default:{
        abort = 1;
      }break;
    }
    if(abort == 0){
      // Send to task M mailbox
    }
    taskCState.lastComplete = chVTGetSystemTime();
    taskCState.lastDeadline = taskCState.nextDeadline;
    ++taskCState.completesSinceLastCheck;
  }
}

// Try to fail other tasks, using methods that work on naive task schedulers (100% utilization, short tasks, acquire unused resources indefinately, aqcuire random resources)
void taskF(void) {
  // Three task states
  // Fail NPC, hold a random mutex and sleep
  const uint8_t acquireResources = 0;
  // Fails RM, shortest task but constant
  const uint8_t shortTask = 1;
  // Fails any non-preemptive scheduler
  const uint8_t fullUtilization = 2;

  mutex_t mut;
  chMtxObjectInit(&mut);
  
  uint8_t currentTask = acquireResources;
  // Prevent compiler optimization of expensive operation
  volatile double num = (double)(int32_t)mut.owner;
  volatile double den = (num-1.1) * 1.7;
  while(1){
    switch(currentTask){
      case acquireResources:{
        // Acquire random mutex, hold it for 1 second (long enough to fail other tasks), then release it
        // NPC would prevent preemption while lock is held, ChibiOS should not
        chMtxLock(&mut);
        chThdSleep(TIME_MS2I(1000));
        chMtxUnlock(&mut);

        updateTaskState(&taskFState, 1, 100);
        // Wait until next release
        chThdSleepUntil(taskFState.nextWake);
        
        currentTask = shortTask;
      }break;
      case shortTask:{
        // Run 1ms tasks every ms for 1 second
        // RM would fail, since this is the shortest task
        for(uint_fast16_t i=0;i<1000;++i){
          // Burn some clock cycles
          double s = sqrt(sin(cos(tan(num/den))));
          updateTaskState(&taskFState, 1, 100);
          // Wait until next release
          chThdSleepUntil(taskFState.nextWake);
        }
        currentTask = fullUtilization;
        // Next task has different deadline requirements
        updateTaskState(&taskFState, 100, 10000);
        // Wait until next release
        chThdSleepUntil(taskFState.nextWake);
      }break;
      case fullUtilization:{
        for(uint16_t i=0;i<10000;++i){
          // Burn some clock cycles
          for(uint16_t j=0;j<100;++j){
            volatile double s = sqrt(sin(cos(tan(num/den))));
          }
        }
        updateTaskState(&taskFState, 2000, 100);
        // Wait until next release
        chThdSleepUntil(taskFState.nextWake);
        currentTask = acquireResources;
      };break;
    }
  }
}
