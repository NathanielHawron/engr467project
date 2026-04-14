#include "taskStats.h"

void updateTaskState(TaskState *taskState, int wakeupDelay, int maxTimeToComplete){
    // Move current stats into previous stats
    taskState->lastComplete = chVTGetSystemTime();
    taskState->lastDeadline = taskState->nextDeadline;
    // Determine next wakeup and deadline timestamp
    taskState->nextWake = chTimeAddX(taskState->nextWake, TIME_MS2I(wakeupDelay));
    taskState->nextDeadline = chTimeAddX(taskState->nextWake, TIME_MS2I(maxTimeToComplete));
    // Increment complete count, should be at most 1 when checked once per frame
    ++taskState->completesSinceLastCheck;
}

void reviewTask(TaskStats* stats, TaskState* state) {
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
