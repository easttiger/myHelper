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

  namespace ran {
    namespace int_hash_fn {
      __host__ __device__
      unsigned int twong7(unsigned int a) { 
        //http://burtleburtle.net/bob/hash/integer.html
        a = (a + 0x7ed55d16) + (a << 12);
        a = (a ^ 0xc761c23c) ^ (a >> 19);
        a = (a + 0x165667b1) + (a << 5);
        a = (a + 0xd3a2646c) ^ (a << 9);
        a = (a + 0xfd7046c5) + (a << 3);
        a = (a ^ 0xb55a4f09) ^ (a >> 16);
        return a;
      }

    }
    namespace gen {      
      struct runif_gen{
        __host__ __device__
        float operator()(unsigned int a) {
          return static_cast<float>(int_hash_fn::twong7(a)) / UINT_MAX;
        }
      };
    }
    __host__ __device__
    void runif(thrust::device_vector<float>& d_v) {      
      thrust::tabulate(d_v.begin(), d_v.end(), gen::runif_gen());
    }
  }
}
