#pragma once

#include <stdint.h>
#include "ch.h"

typedef struct _task_state {
    systime_t nextWake, nextDeadline, lastComplete, lastDeadline;
    uint32_t completesSinceLastCheck;
} TaskState;
typedef struct _task_stats {
    uint32_t period;
    // Previous nextWake
    uint32_t lastWake;
    uint32_t duration;
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

inline void reviewTask(TaskStats* stats, TaskState* state) {
    // Ignore tasks that haven't completed since last check
    if(state->completesSinceLastCheck == 0){
        return;
    }
    state->completesSinceLastCheck = 0;
    // Completing after deadline means failure
    if(state->lastComplete > state->lastDeadline){
        ++stats->failureCount;
    }
    stats->period = state->nextDeadline - state->lastDeadline;
    stats->duration = state->lastComplete - stats->lastWake;
    stats->lastWake = state->nextWake;
}
