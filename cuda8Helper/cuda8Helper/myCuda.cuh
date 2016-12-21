#ifndef _MY_CUDA_CUH_
#define _MY_CUDA_CUH_

// CUDA headers
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cublas_v2.h"

// C headers
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// C++ headers
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

using namespace std;

namespace myCuda {
  void gpuInfo();
  namespace math {
    __device__ float logit1(const float x);
    __global__ void logit(float* y, const float* x, int leng);
  }

  
  namespace print {
    __global__ void print_float(float* x, int leng);
    __global__ void print_int(int* x, int leng);
    __global__ void print_double(double* x, int leng);
    __global__ void print_long(long* x, int leng);
    __global__ void print_char(char* x, int leng);
    __global__ void print_cstr(char** x, int leng);
  }

}
#endif