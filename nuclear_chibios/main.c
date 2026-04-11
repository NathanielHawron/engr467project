#include "ch.h"
#include "hal.h"

#include "tasks.h"

#define BLINK_MAILBOX_SIZE 128U

static msg_t mbBlink_buffer[BLINK_MAILBOX_SIZE];
static mailbox_t mbBlink;

static THD_WORKING_AREA(waThread_B, 128);
static THD_WORKING_AREA(waThread_CB, 128);

static THD_FUNCTION(Thread_B, arg) {
  (void)arg;
  taskB();
}

static THD_FUNCTION(Thread_CB, arg) {
  taskCB((mailbox_t *)arg);
}

int main() {
  halInit();
  chSysInit();
  chMBObjectInit(&taskBInbox, &taskBInboxBuffer, 1);

  chMBObjectInit(&mbBlink, mbBlink_buffer, MAILBOX_SIZE);

  chThdCreateStatic(waThread_B, sizeof(waThread_B), NORMALPRIO, Thread_B, &mbBlink);
  chThdCreateStatic(waThread_CB, sizeof(waThread_CB), NORMALPRIO, Thread_CB, &mbBlink);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
