
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "myCuda.cuh"
#include <stdio.h>

__device__ float logit1(float x) {
  return expf(x) / (1. + expf(x));
}
__global__ void logit(float* y, float* x, int leng) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i < leng) {
    y[ i ] = logit1(x[ i ]);
  }
}

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

