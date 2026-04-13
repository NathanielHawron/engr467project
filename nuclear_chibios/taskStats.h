#pragma once

#include <stdint.h>
#include "ch.h"

typedef struct _task_state {
    systime_t nextWake, nextDeadline, lastComplete, lastDeadline;
    uint32_t completesSinceLastCheck;
} TaskState;
typedef struct _task_stats {
    uint32_t period;
    uint32_t durationHistory[100];
    uint32_t duration;
    uint_fast8_t durationHistoryIndex;
    uint32_t rejectionCount;
    uint32_t failureCount;
} TaskStats;

// wakeupDelay is period
inline void updateTaskState(TaskState *taskState, int wakeupDelay, int maxTimeToComplete){
    // Move current stats into previous stats
    taskState->lastComplete = chVTGetSystemTime();
    taskState->lastDeadline = taskBState.nextDeadline;
    // Determine next wakeup and deadline timestamp
    taskState->nextWake += TIME_MS2I(wakeupDelay);
    taskState->nextDeadline = taskState->nextWake + TIME_MS2I(maxTimeToComplete);
    // Increment complete count, should be at most 1 when checked once per frame
    ++taskState->completesSinceLastCheck;
}

inline void reviewTask(TaskStats* stat, TaskState* ts) {
    // do something...
}
