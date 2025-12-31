#ifndef GPU_OPTIMIZE_
#define GPU_OPTIMIZE_

extern "C"
{
    __declspec(dllexport) int NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#endif