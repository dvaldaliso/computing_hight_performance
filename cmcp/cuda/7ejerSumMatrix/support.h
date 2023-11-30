/******************************************************************************
 *cr
 *cr            (C) Copyright 2010 The Board of Trustees of the
 *cr                        University of Illinois
 *cr                         All Rights Reserved
 *cr
 ******************************************************************************/

#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <sys/time.h>

typedef struct {
    struct timeval startTime;
    struct timeval endTime;
} Timer;

void verify(float *A, float *B, float *C, int n);
void startTime(Timer* timer);
void stopTime(Timer* timer);
float elapsedTime(Timer timer);

#define FATAL(msg) \
    do {\
        fprintf(stderr, "[%s:%d] %s\n", __FILE__, __LINE__,(msg));\
        exit(-1);\
    } while(0)

#endif
