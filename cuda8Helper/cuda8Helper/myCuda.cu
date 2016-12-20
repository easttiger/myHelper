#include "myCuda.cuh"

namespace myCuda {
  void gpuInfo() {
    int nDevices;
    cudaGetDeviceCount(&nDevices);
    for(int i = 0; i < nDevices; ++i) {
      cudaDeviceProp prop;
      cudaGetDeviceProperties(&prop, i);
      printf("Device %d:\n",i);
      printf("  Device name: %s\n", prop.name);
      printf("  Compute Capability: %d.%d\n", prop.major, prop.minor);
      printf("  Memory Clock Rate (KHz): %d\n", prop.memoryClockRate);
      printf("  Memory Bus Width (bits): %d\n", prop.memoryBusWidth);
      printf("  Peak Memory Bandwith (GB/s): %f\n", 2. * prop.memoryClockRate * (prop.memoryBusWidth / 8.) / 1.e6);      
    }
  }
}
