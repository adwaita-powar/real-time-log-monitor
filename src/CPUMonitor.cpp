#include "../include/CPUMonitor.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

void CPUMonitor::start()
{
    long prevIdle = 0, prevTotal = 0;

    // First baseline read
    {
        std::ifstream file("/proc/stat");
        std::string line;
        std::getline(file, line);

        std::istringstream ss(line);
        std::string cpu;
        long user, nice, system, idle, iowait, irq, softirq, steal;

        ss >> cpu >> user >> nice >> system >> idle
           >> iowait >> irq >> softirq >> steal;

        prevIdle = idle + iowait;
        prevTotal = user + nice + system + idle +
                    iowait + irq + softirq + steal;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (true)
    {
        std::ifstream file("/proc/stat");
        std::string line;
        std::getline(file, line);

        std::istringstream ss(line);
        std::string cpu;
        long user, nice, system, idle, iowait, irq, softirq, steal;

        ss >> cpu >> user >> nice >> system >> idle
           >> iowait >> irq >> softirq >> steal;

        long idleTime = idle + iowait;
        long totalTime = user + nice + system + idle +
                         iowait + irq + softirq + steal;

        long deltaIdle = idleTime - prevIdle;
        long deltaTotal = totalTime - prevTotal;

        float usage = 0.0f;
        if (deltaTotal > 0)
            usage = 100.0f * (1.0f - (float)deltaIdle / deltaTotal);

        cpuUsage.store(usage);

        prevIdle = idleTime;
        prevTotal = totalTime;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

float CPUMonitor::getCPUUsage() const
{
    return cpuUsage.load();
}