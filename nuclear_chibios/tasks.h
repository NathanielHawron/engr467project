#pragma once

#include "taskStats.h"

// Blink built-in LED at a frequency
TaskState taskBState;
void taskB();
// Set the frequency of taskB using ICP
TaskState taskCBState;
void taskCB();
// Monitor all other tasks for period, duration, average actual duration, and failure/rejection counts
TaskState taskMState;
void taskM();
// Send taskM data over Serial using IPC, non-preemptable
TaskState taskSState;
void taskS();
// Compute math operations provided by Serial, non-preemptable
TaskState taskCState;
void taskC();
// Try to fail other tasks, using methods that work on naive task schedulers (100% utilization, short tasks, acquire unused resources indefinately, aqcuire random resources)
TaskState taskFState;
void taskF();
