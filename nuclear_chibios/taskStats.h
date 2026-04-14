#pragma once

#include <stdint.h>
#include "ch.h"

typedef struct _task_state {
    systime_t nextWake, lastWake, nextDeadline, lastComplete, lastDeadline;
    uint32_t completesSinceLastCheck;
} TaskState;
typedef struct _task_stats {
    uint32_t period;
    uint32_t lastWake;
    uint32_t duration;
    uint32_t failureCount;
} TaskStats;

// wakeupDelay is period
void updateTaskState(TaskState *taskState, int wakeupDelay, int maxTimeToComplete);

void reviewTask(TaskStats* stats, TaskState* state);

