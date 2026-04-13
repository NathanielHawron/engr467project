#include "tasks.h"
#include "taskStats.h"

#include "ch.h"
#include "hal.h"

// Blink built-in LED at a frequency
void taskB(void) {
  // In ms
  static int blinkDuration = 1000;
  // Time between release and dedline
  static int maxDelay = 100;

  TaskState taskBState = { 0 };

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

  TaskState taskCBState = { 0 };

  while(1){
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
  TaskState taskMState = { 0 };
  while(1){
  }
}
// Send taskM data over Serial using IPC, non-preemptable
void taskS(void) {
  TaskState taskSState = { 0 };
  // Enter critical section
  chSysLock();

  // Leave critical section
  chSysUnlock();
}
// Compute math operations provided by Serial, non-preemptable
void taskC(void) {
  TaskState taskCState = { 0 };
  // Enter critical section
  chSysLock();

  // Leave critical section
  chSysUnlock();
}
// Try to fail other tasks, using methods that work on naive task schedulers (100% utilization, short tasks, acquire unused resources indefinately, aqcuire random resources)
void taskF(void) {
  TaskState taskFState = { 0 };

}
