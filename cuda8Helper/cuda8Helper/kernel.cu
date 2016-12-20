
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "myCuda.cuh"
#include <stdio.h>
using namespace myCuda::math;
int main() {
  const int N = 1024;
  float* x; cudaMallocManaged(&x, N * sizeof(float));
  float* y; cudaMallocManaged(&y, N * sizeof(float));
  for(int i = 0; i < N; ++i) {
    x[ i ] = (i - N / 2.) / N;
  }
  logit <<<1, N>>>(y, x, N);
  cudaDeviceSynchronize();
  for(int i = 0; i < N; ++i) {
    printf("logit(%f)=%f\n", x[ i ], y[ i ]);
  }
  cudaFree(x);
  cudaFree(y);
  system("pause");
  return  0;
}

