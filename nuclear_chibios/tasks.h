#pragma once

// Blink built-in LED at a frequency
void taskB();
// Set the frequency of taskB using ICP
void taskCB();
// Monitor all other tasks for period, duration, average actual duration, and failure/rejection counts
void taskM();
// Send taskM data over Serial using IPC, non-preemptable
void taskS();
// Compute math operations provided by Serial, non-preemptable
void taskC();
// Try to fail other tasks, using methods that work on naive task schedulers (100% utilization, short tasks, acquire unused resources indefinately, aqcuire random resources)
void taskF();
