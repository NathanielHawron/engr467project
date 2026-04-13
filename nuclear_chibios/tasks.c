#include "tasks.h"

#include "hal.h"
#include "board.h"

// Blink built-in LED at a frequency
void taskB() {
  // In ms
  static int blinkDuration = 1000;
  // Time between release and dedline
  static int maxDelay = 100;

  while (1) {
    // Start Task
    palToggleLine(LINE_LED_GREEN);
    msg_t msg;
    if(chMBFetchI(taskBInbox,&msg) == MSG_OK){
      blinkDuration = (int)msg;
    }
    // End Task
    
    // Move current stats into previous stats
    taskBState.lastComplete = chVTGetSystemTime();
    taskBState.lastDeadline = taskBState.nextDeadline;
    // Determine next wakeup and deadline timestamp
    taskBState.nextWake += TIME_MS2I(blinkDuration);
    taskBState.nextDeadline = taskBState.nextWake + TIME_MS2I(maxDelay);
    // Increment complete count, should be at most 1 when checked once per frame
    ++taskBState.completesSinceLastCheck;
    // Wait until next release
    chThdSleepUntil(taskBState.nextWake);
  }
}
// Set the frequency of taskB using ICP
void taskCB() {
  // In ms
  static int changeDelay = 10000;
  // Time between release and deadline
  static int maxDelay = 100;
  static int durations[10] = {
    1000, 750, 500, 250, 100, 50, 150, 400, 700, 1500
  };
  static int durationIndex = 0;
  while(1){
    // Start Task
    durationIndex = (durationIndex+1)%10;
    chMBPostI(taskBInbox, (msg_t)durations[durationIndex]);
    // End Task
    
    // Move current stats into previous stats
    taskCBState.lastComplete = chVTGetSystemTime();
    taskCBState.lastDeadline = taskCBState.nextDeadline;
    // Determine next wakeup and deadline timestamp
    taskCBState.nextWake += TIME_MS2I(blinkDuration);
    taskCBState.nextDeadline = taskCBState.nextWake + TIME_MS2I(maxDelay);
    // Increment complete count, should be at most 1 when checked once per frame
    ++taskCBState.completesSinceLastCheck;
    // Wait until next release
    chThdSleepUntil(e.nextWake);
  }
}
// Monitor all other tasks for period, duration, average actual duration, and failure/rejection counts
void taskM() {
  while(1){
  }
}
// Send taskM data over Serial using IPC, non-preemptable
void taskS() {
  // Enter critical section
  chSysLock();

  // Leave critical section
  chSysUnlock();
}
// Compute math operations provided by Serial, non-preemptable
void taskC() {
  // Enter critical section
  chSysLock();

  // Leave critical section
  chSysUnlock();
}
// Try to fail other tasks, using methods that work on naive task schedulers (100% utilization, short tasks, acquire unused resources indefinately, aqcuire random resources)
void taskF() {

}
