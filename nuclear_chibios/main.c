#include "ch.h"
#include "hal.h"

#include "tasks.h"


msg_t taskBInboxBuffer;
mailbox_t taskBInbox;

static THD_WORKING_AREA(waThread_B, 128);
static THD_WORKING_AREA(waThread_CB, 128);

static THD_FUNCTION(Thread_B, arg) {
  taskB();
}

static THD_FUNCTION(Thread_CB, arg) {
  taskCB();
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
