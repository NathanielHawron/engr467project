#include "tasks.h"
#include "taskStats.h"

#include <string.h>

#include "ch.h"
#include "hal.h"
#include "oop_chprintf.h"

// Enters a critical section, runs code, then leaves (ensures lock/unlock pairs)
#define CRITICAL_SECTION(x) do { \
  chSysLock();      \
  x                  \
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

// Set the frequency of taskB using ICP
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
    
    updateTaskState(&taskCState, changeDelay, maxDelay);
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
  const char* msg = "Hello, World!\r\n";

  TaskState *taskStates[6] = {
    &taskBState, &taskCBState, &taskMState, &taskSState, &taskCState, &taskFState
  };

  static int period = 500;
  static int maxDelay = 500;
  
  while(1) {
    CRITICAL_SECTION(
      sdWriteTimeout(&SD2, (const uint8_t *)msg, strlen(msg), TIME_IMMEDIATE);
    )
    updateTaskState(&taskMState, period, maxDelay);
    // Wait until next release
    chThdSleepUntil(taskMState.nextWake);
  }
}

// Compute math operations provided by Serial, non-preemptable
void taskC(void) {
  
  while(1){
    CRITICAL_SECTION(
  
    )
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
  while(1){
    switch(currentTask){
      case acquireResources:{
        // Acquire random mutex, hold it for 1 second (long enough to fail other tasks), then release it
        // NPC would prevent preemption while lock is held, ChibiOS should not
        chMtxLock(&mut);
        chThdSleepFor(TIME_MS2I(1000));
        chMtxUnlock(&mut);

        updateTaskState(&taskMState, 500, 100);
        // Wait until next release
        chThdSleepUntil(taskMState.nextWake);
      }break;
      case shortTask:{

      }break;
      case fullUtilization:{

      };break;
    }
  }
}
