#pragma once

#include "taskStats.h"
#include "ch.h"


// Blink built-in LED at a frequency
extern TaskState taskBState; // defined in main.c !
extern mailbox_t taskBInbox; // defined in main.c !
extern msg_t taskBInboxBuffer;
void taskB(void);
// Set the frequency of taskB using IPC
extern TaskState taskCBState;
void taskCB(void);
// Monitor all other tasks for period, duration, average actual duration, and failure/rejection counts
extern TaskState taskMState;
extern TaskStats taskStats[6];
extern mutex_t taskStatsMutex;
void taskM(void);
// Send taskM data over Serial using IPC, non-preemptable
extern TaskState taskSState;
void taskS(void);
// Compute math operations provided by Serial, non-preemptable
extern TaskState taskCState;
void taskC(void);
// Try to fail other tasks, using methods that work on naive task schedulers (100% utilization, short tasks, acquire unused resources indefinately, aqcuire random resources)
extern TaskState taskFState;
void taskF(void);
