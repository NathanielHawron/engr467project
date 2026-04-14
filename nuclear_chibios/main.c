#include "ch.h"
#include "hal.h"

#include "tasks.h"

static SerialConfig uartCfg = {
  .speed = 115200,
  .cr2 = USART_CR2_STOP1_BITS
};

msg_t taskBInboxBuffer;
mailbox_t taskBInbox;

mutex_t taskStatsMutex;

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

  sdStart(&SD2, &uartCfg);

  chThdCreateStatic(waThread_B, sizeof(waThread_B), NORMALPRIO+4, Thread_B, NULL);
  chThdCreateStatic(waThread_CB, sizeof(waThread_CB), NORMALPRIO+5, Thread_CB, NULL);
  chThdCreateStatic(waThread_M, sizeof(waThread_M), NORMALPRIO+3, Thread_M, NULL);

  chThdCreateStatic(waThread_S, sizeof(waThread_S), NORMALPRIO+2, Thread_S, NULL);
  chThdCreateStatic(waThread_C, sizeof(waThread_C), NORMALPRIO, Thread_C, NULL);
  chThdCreateStatic(waThread_F, sizeof(waThread_F), NORMALPRIO+1, Thread_F, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
