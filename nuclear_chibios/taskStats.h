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

inline void reviewTask(TaskStats* stat, TaskState* ts) {
    // do something...
}
