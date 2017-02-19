
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "myCuda.cuh"
#include <stdio.h>
using namespace myCuda::math;
const int lena = 83;
const int lenb = 1543;
float a[ lena ], b[ lenb ], x[ lena ], xnew[ lena ], tau[ lenb ];
int De[ lena * lenb ];
int tDe[ lenb * lena ];

int unified_memory() {
  const int N = 4;
  float* x; cudaMallocManaged(&x, N * sizeof(float));
  float* y; cudaMallocManaged(&y, N * sizeof(float));
  for(int i = 0; i < N; ++i) {
    x[ i ] = (i - N / 2.) / N;
  }
  logit <<<1, N >>>(y, x, N);
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

inline float sum(float* a, const int lena) {
  float res = *a;
  for(int i = 1; i < lena; ++i) {
    res += a[ i ];
  }
  return res;
}
void transpose(int* tm, int* m, const int nrow, const int ncol) {
  for(int i = 0; i < nrow; ++i) {
    for(int j = 0; j < ncol; ++j) {
      tm[ j * nrow + i ] = m[ i * ncol + j ];
    }
  }
}
float M_v(int* M, int row, float* v, const int len) {
  float res = 0.;
  int* p = M + row * len;
  for(int i = 0; i < len; ++i) {
    if(*p++) res += v[i];
  }
  return res;
}

void cpuweaver(float tol) {
  float sa = sum(a, lena);
  for(int i = 0; i < lena; ++i) x[ i ] = a[ i ] / sa;
  float m = sa + sum(b, lenb);
  
  int iter = 0;
  float e = 999, tmp;
  for(iter = 0; e > 1e-15; ++iter) {
    for(int j = 0; j < lenb; ++j) {
      tau[ j ] = b[ j ] / M_v(tDe, j, x, lena);
    }
    for(int i = 0; i < lena; ++i) {
      xnew[ i ] = a[ i ] / (m - M_v(De, i, tau, lenb));
    }
    e = 0.;
    for(int i = 0; i < lena; ++i) {
      tmp = fabs(xnew[ i ] - x[ i ]);
      if(e < tmp) e = tmp;
    };
    for(int i = 0; i < lena; ++i) {
      x[ i ] = xnew[ i ];
    }
  }
}

void test_weaver() {
  FILE* fp;
  //load a
  fp = fopen("C:/Users/easttiger/Dropbox/Subjects/W/Weaver Paper Reading list/Hunter matlab code/a.txt", "r");
  for(int i = 0; i < lena; ++i) {
    fscanf(fp, "%f\n", a + i);
  }
  fclose(fp);
  //load b
  fp = fopen("C:/Users/easttiger/Dropbox/Subjects/W/Weaver Paper Reading list/Hunter matlab code/b.txt", "r");
  for(int i = 0; i < lenb; ++i) {
    fscanf(fp, "%f\n", b + i);
  }
  fclose(fp);
  //load b
  fp = fopen("C:/Users/easttiger/Dropbox/Subjects/W/Weaver Paper Reading list/Hunter matlab code/tDe.txt", "r");
  for(int j = 0; j < lenb; ++j) {
    for(int i = 0; i < lena - 1; ++i) {
      fscanf(fp, "%d ", tDe + j * lena + i);
    }
    fscanf(fp, "%d\n", tDe + (j + 1) * lena - 1);
  }
  fclose(fp);

  //initialize De as transpose of tDe
  transpose(De, tDe, lenb, lena);

  
  cpuweaver(0.00000001);
  for(int i = 0; i < lena; ++i) {
    printf("%f,", x[ i ]);
  }
}


int main() {
  myCuda::gpuInfo();
  test_random_number();
  test_weaver();
  system("pause");
  return  0;
}
