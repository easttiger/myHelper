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
}

