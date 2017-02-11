
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "myCuda.cuh"
#include <stdio.h>
using namespace myCuda::math;

int unified_memory() {
  const int N = 4;
  float* x; cudaMallocManaged(&x, N * sizeof(float));
  float* y; cudaMallocManaged(&y, N * sizeof(float));
  for(int i = 0; i < N; ++i) {
    x[ i ] = (i - N / 2.) / N;
  }
  logit << <1, N >> >(y, x, N);
  cudaDeviceSynchronize();
  for(int i = 0; i < N; ++i) {
    printf("logit(%f)=%f\n", x[ i ], y[ i ]);
  }
  cudaFree(x);
  cudaFree(y);
  return 0;
}

#define IDX2F(i,j,ld)((((j)-1)*(ld)+((i)-1)))
static __inline__ void modify(cublasHandle_t handle, float* m, int ldm, int n, int p, int q, float alpha, float beta) {
  cublasSscal(handle, n-p+1, &alpha, &m[IDX2F(p,q,ldm)], ldm);
  cublasSscal(handle, ldm-p+1, &beta, &m[IDX2F(p,q,ldm)], 1);
}

int cublas_test() {
  const int M = 6;
  const int N = 5;
  cudaError_t cudaStat;
  cublasStatus_t stat;
  cublasHandle_t handle;
  int i, j;
  float* devPtrA;
  float* a = 0;
  a = (float*)malloc(M * N * sizeof(*a));
  for(j = 1; j <= N; ++j) {
    for(i = 1; i <= M; ++i) {
      a[ IDX2F(i, j, M) ] = (float)((i - 1) * M + j);
    }
  }
  return 0;
}

void test_random_number() {
  thrust::device_vector<float> d(10);
  myCuda::ran::runif(d);
  thrust::copy(d.begin(), d.end(), std::ostream_iterator<float>(std::cout, "\n"));
}

int main() {
  myCuda::gpuInfo();
  test_random_number();
  system("pause");
  return  0;
}
