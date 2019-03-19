#include <time.h>

double delta_ms(struct timespec start, struct timespec end)
{
    return (((end.tv_sec - start.tv_sec) * 1e+9
           + (end.tv_nsec - start.tv_nsec)) * 1e-6);
}