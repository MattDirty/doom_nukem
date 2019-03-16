#include "doom.h"

Uint64     ms_since_last_frame(int last_frame)
{
    struct timespec current_time;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &current_time);
    return (current_time.tv_nsec / 1000000 - last_frame);
}