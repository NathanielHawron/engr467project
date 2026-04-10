#pragma once

#include <cstdint>
#include "chtime.h"

class TaskState{
    systime_t nextWake, nextDeadline, lastComplete, lastDeadline;
    uint32_t completesSinceLastCheck;
};
class TaskStats{
    uint32_t period;
    uint32_t durationHistory[100];
    uint32_t duration;
    uint_fast8_t durationHistoryIndex;
    uint32_t rejectionCount;
    uint32_t failureCount;
    void reviewTask(TaskState ts){

    }
};