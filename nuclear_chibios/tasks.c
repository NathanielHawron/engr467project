#include "tasks.h"

#include "ch.h"
#include "hal.h"
#include "board.h"
#include "chmboxes.h"

// Blink built-in LED at a frequency
void taskB() {
  // in ms
  static int blinkDuration = 1000;
  static int maxDelay = 100;

  while (1) {
    // Start Task
    palToggleLine(LINE_LED_GREEN);
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
    chThdSleepUntil(e.nextWake);
  }
}
// Set the frequency of taskB using ICP
void taskCB(mailbox_t* mb) {
  static int newBlinkDuration = 500;

  chThdSleepMicroseconds(5000);

  (void)chMBPostTimeout(mb, newBlinkDuration, TIME_INFINITE);

  chThdExit(MSG_OK);
  //while (true) { }
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
