#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "support.h"

void verify(float *A, float *B, float *C, int n) {

  const float relativeTolerance = 1e-6;

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      float sum = A[i+j*n] + B[i+j*n];
      float relativeError = (sum - C[i+j*n])/sum;
      if (relativeError > relativeTolerance
        || relativeError < -relativeTolerance) {
        printf("TEST FAILED\n\n");
        exit(0);
      }
    }
  }
  printf("TEST PASSED\n\n");

}

void startTime(Timer* timer) {
    gettimeofday(&(timer->startTime), NULL);
}

void stopTime(Timer* timer) {
    gettimeofday(&(timer->endTime), NULL);
}

float elapsedTime(Timer timer) {
    return ((float) ((timer.endTime.tv_sec - timer.startTime.tv_sec) \
                + (timer.endTime.tv_usec - timer.startTime.tv_usec)/1.0e6));
}

