#include "myCuda.cuh"

namespace myCuda {
#define Dim(x, type, length) \
  type * x; cudaMallocManaged(&x, sizeof(type)* length)

  void gpuInfo() {
    int nDevices;
    cudaGetDeviceCount(&nDevices);
    for(int i = 0; i < nDevices; ++i) {
      cudaDeviceProp prop;
      cudaGetDeviceProperties(&prop, i);
      printf("Device %d:\n", i);
      printf("  Device name: %s\n", prop.name);
      printf("  Compute Capability: %d.%d\n", prop.major, prop.minor);
      printf("  Memory Clock Rate (KHz): %d\n", prop.memoryClockRate);
      printf("  Memory Bus Width (bits): %d\n", prop.memoryBusWidth);
      printf("  Peak Memory Bandwith (GB/s): %f\n", 2. * prop.memoryClockRate * (prop.memoryBusWidth / 8.) / 1.e6);
    }
  }


  namespace print {
    __global__ void print_float(float* x, int leng) {
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      if(i < leng) {
        printf("%f,", x[ i ]);
      }
    }

    __global__ void print_int(int* x, int leng) {
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      if(i < leng) {
        printf("%d,", x[ i ]);
      }
    }

    __global__ void print_double(double* x, int leng) {
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      if(i < leng) {
        printf("%lf,", x[ i ]);
      }
    }

    __global__ void print_long(long* x, int leng) {
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      if(i < leng) {
        printf("%ld,", x[ i ]);
      }
    }

    __global__ void print_char(char* x, int leng) {
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      if(i < leng) {
        printf("%s,", x[ i ]);
      }
    }

    __global__ void print_cstr(char** x, int leng) {
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      if(i < leng) {
        printf("%s,", x[ i ]);
      }
    }
  }


  namespace math {
    __device__ float logit1(const float x) {
      return expf(x) / (1. + expf(x));
    }

    __global__ void logit(float* y, const float* x, int leng) {
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      if(i < leng) {
        y[ i ] = logit1(x[ i ]);
      }
    }
  }
}
