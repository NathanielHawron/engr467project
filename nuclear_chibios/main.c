#include "ch.h"
#include "hal.h"

#include "tasks.h"


msg_t taskBInboxBuffer;
mailbox_t taskBInbox;

static THD_WORKING_AREA(waThread_B, 128);
static THD_WORKING_AREA(waThread_CB, 128);
static THD_WORKING_AREA(waThread_M, 128);
static THD_WORKING_AREA(waThread_S, 128);
static THD_WORKING_AREA(waThread_C, 128);
static THD_WORKING_AREA(waThread_F, 128);

static THD_FUNCTION(Thread_B, arg) {
  taskB();
}

static THD_FUNCTION(Thread_CB, arg) {
  taskCB();
}

static THD_FUNCTION(Thread_M, arg) {
  taskM();
}

static THD_FUNCTION(Thread_S, arg) {
  taskS();
}

static THD_FUNCTION(Thread_C, arg) {
  taskC();
}

static THD_FUNCTION(Thread_F, arg) {
  taskF();
}

int main(void) {
  halInit();
  chSysInit();
  chMBObjectInit(&taskBInbox, &taskBInboxBuffer, 1);
  chMtxObjectInit(&taskStatsMutex);


  chThdCreateStatic(waThread_B, sizeof(waThread_B), NORMALPRIO, Thread_B, NULL);
  chThdCreateStatic(waThread_CB, sizeof(waThread_CB), NORMALPRIO, Thread_CB, NULL);
  chThdCreateStatic(waThread_M, sizeof(waThread_M), NORMALPRIO, Thread_M, NULL);

  // chThdCreateStatic(waThread_S, sizeof(waThread_S), NORMALPRIO, Thread_S, NULL);
  // chThdCreateStatic(waThread_C, sizeof(waThread_C), NORMALPRIO, Thread_C, NULL);
  // chThdCreateStatic(waThread_F, sizeof(waThread_F), NORMALPRIO, Thread_F, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
