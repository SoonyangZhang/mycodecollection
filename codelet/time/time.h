#ifndef TIME_H
#define TIME_H
#include <stdint.h>
#include <time.h>
#define kNumMillisecsPerSec INT64_C(1000)
#define kNumMicrosecsPerSec  INT64_C(1000000)
#define kNumNanosecsPerSec  INT64_C(1000000000)

#define kNumMicrosecsPerMillisec (kNumMicrosecsPerSec / kNumMillisecsPerSec)
#define kNumNanosecsPerMillisec (kNumNanosecsPerSec / kNumMillisecsPerSec)
#define kNumNanosecsPerMicrosec (kNumNanosecsPerSec / kNumMicrosecsPerSec)
int64_t SystemTimeMillis();
#endif
