#include "ch.h"
#include "hal.h"

#include "tasks.h"


msg_t taskBInboxBuffer;   // extern <- tasks.h !
mailbox_t taskBInbox;     // extern <- tasks.h !

static THD_WORKING_AREA(waThread_B, 128);
static THD_WORKING_AREA(waThread_CB, 128);

mutex_t taskStatsMutex; // extern <- tasks.h !
TaskStats taskStats[6] = {{ 0 }}; // extern <- tasks.h !

static THD_FUNCTION(Thread_B, arg) {
  (void)arg;
  taskB();
}

static THD_FUNCTION(Thread_CB, arg) {
  (void)arg;
  taskCB();
}

static THD_FUNCTION(Thread_M, arg) {
  (void)arg;
  taskM();
}

static THD_FUNCTION(Thread_S, arg) {
  (void)arg;
  taskS();
}

static THD_FUNCTION(Thread_C, arg) {
  (void)arg;
  taskC();
}

static THD_FUNCTION(Thread_F, arg) {
  (void)arg;
  taskF();
}

int main(void) {
  halInit();
  chSysInit();
  chMBObjectInit(&taskBInbox, &taskBInboxBuffer, 1);

  chThdCreateStatic(waThread_B, sizeof(waThread_B), NORMALPRIO, Thread_B, NULL);
  chThdCreateStatic(waThread_CB, sizeof(waThread_CB), NORMALPRIO, Thread_CB, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
