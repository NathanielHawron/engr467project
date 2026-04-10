#include "ch.h"
#include "hal.h"

#include "tasks.h"

static THD_WORKING_AREA(waThread_B, 128);
static THD_FUNCTION(Thread_B, args) {
  (void)args;
  taskB();
}

int main() {
  halInit();
  chSysInit();

  chThdCreateStatic(waThread_B, sizeof(waThread_B), NORMALPRIO, Thread_B, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
