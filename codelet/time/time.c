#include <stdint.h>
#include <sys/time.h>
#include "time.h"
int64_t SystemTimeNanos() {
  int64_t ticks;
    struct timespec ts;
  // TODO(deadbeef): Do we need to handle the case when CLOCK_MONOTONIC is not
  // supported?
  clock_gettime(CLOCK_MONOTONIC, &ts);
  ticks = kNumNanosecsPerSec * (int64_t)(ts.tv_sec) +(int64_t)ts.tv_nsec;
  return ticks;
}
int64_t SystemTimeMillis() {
  return (int64_t)(SystemTimeNanos() / kNumNanosecsPerMillisec);
}
