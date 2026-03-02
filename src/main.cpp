#include "../include/Dashboard.h"
#include "../include/AlertManager.h"
#include "../include/CPUMonitor.h"
#include "../include/LogGenerator.h"
#include <thread>

int main()
{
    AlertManager alertManager;
    CPUMonitor cpuMonitor;
    LogGenerator logGenerator;
    Dashboard dashboard;

    std::thread cpuThread(&CPUMonitor::start, &cpuMonitor);

    std::thread logThread(&LogGenerator::start,
                          &logGenerator,
                          std::ref(alertManager));

    dashboard.start(alertManager, cpuMonitor);

    cpuThread.join();
    logThread.join();

    return 0;
}