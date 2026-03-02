#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <atomic>

class CPUMonitor
{
private:
    std::atomic<float> cpuUsage{0.0f};

public:
    void start();
    float getCPUUsage() const;
};

#endif