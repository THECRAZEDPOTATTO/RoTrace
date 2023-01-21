#include <MinHook.h>
#include <stdio.h>
#include <iostream>
using namespace std;
typedef void (*RenderFunction)();
RenderFunction originalRenderFunction;

void HookedRenderFunction() {
    RenderFunction renderFunction = (RenderFunction)GetProcAddress(GetModuleHandle("Roblox.dll"), "RenderFunction");
    TraceRaysKernel<<<numBlocks, numThreads>>>();
    originalRenderFunction();
}
int main(){
  cudaError_t cudaStatus = cudaSuccess;
  cudaStatus = cudaSetDevice(0);
  cudaStatus = cudaFree(0);
  MH_CreateHook(renderFunction, &HookedRenderFunction, (LPVOID*)&originalRenderFunction);
  MH_EnableHook(MH_ALL_HOOKS);
  RunGame();
  cudaStatus = cudaDeviceReset();
  return 0;

}
