#include "../include/Dashboard.h"
#include "../include/AlertManager.h"
#include "../include/CPUMonitor.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

void Dashboard::printCPUBar(double cpuUsage)
{
    const int barWidth = 50;
    int pos = static_cast<int>((cpuUsage / 100.0f) * barWidth);

    std::cout << "CPU Usage  : ";

    std::string color;
    if (cpuUsage < 50.0)
        color = "\033[1;32m";   // Green
    else if (cpuUsage < 80.0)
        color = "\033[1;33m";   // Yellow
    else
        color = "\033[1;31m";   // Red

    std::cout << color << "[";

    for (int i = 0; i < barWidth; ++i)
        std::cout << (i < pos ? "█" : " ");

    std::cout << "]\033[0m ";

    std::cout << std::fixed << std::setprecision(1)
              << cpuUsage << "%\n";
}

void Dashboard::start(AlertManager& alertManager, CPUMonitor& cpuMonitor)
{
    while (true)
    {
        std::cout << "\033[2J\033[1;1H";

        std::cout << "=============================================================\n";
        std::cout << "        HIGH-PERFORMANCE REAL-TIME SYSTEM MONITOR\n";
        std::cout << "=============================================================\n\n";

        std::cout << "SYSTEM METRICS\n";
        std::cout << "-------------------------------------------------------------\n";

        // ✅ Correct CPU access
        double cpu = cpuMonitor.getCPUUsage();
        printCPUBar(cpu);

        // CPU STATE
        std::cout << "CPU State  : ";

        if (cpu < 30.0)
        {   
          std::cout << "\033[1;32mIDLE\033[0m\n";
        }
        else if (cpu < 60.0)
        {
          std::cout << "\033[1;33mMODERATE LOAD\033[0m\n";
        }
        else if (cpu < 85.0)
        {   
          std::cout << "\033[1;31mHIGH LOAD\033[0m\n";
        }
        else
        {
          std::cout << "\033[5;1;31mOVERLOAD\033[0m\n";
        }

        std::cout << "\nLOG ANALYTICS\n";
        std::cout << "-------------------------------------------------------------\n";

        // ✅ Correct atomic access using .load()
        std::cout << "Total Logs : " << alertManager.total.load() << "\n";
        std::cout << "Logs/sec   : " << alertManager.logsPerSecond.load() << "\n\n";

        std::cout << "\033[1;36mINFO     : " << alertManager.info.load() << "\033[0m\n";
        std::cout << "\033[1;33mWARNING  : " << alertManager.warning.load() << "\033[0m\n";
        std::cout << "\033[1;31mERROR    : " << alertManager.error.load() << "\033[0m\n";
        std::cout << "\033[1;35mCRITICAL : " << alertManager.critical.load() << "\033[0m\n\n";

        // ✅ Compute error rate manually (since not stored)
        int total = alertManager.total.load();
        int error = alertManager.error.load();

        float errorRate = 0.0f;
        if (total > 0)
            errorRate = (error * 100.0f) / total;

        std::cout << "Error Rate : "
                  << std::fixed << std::setprecision(1)
                  << errorRate << "%\n\n";

        std::cout << "ALERT STATUS\n";
        std::cout << "-------------------------------------------------------------\n";

        int criticalCount = alertManager.critical.load();

        if (criticalCount >= 50)
        {
            std::cout << "\033[5;1;31m🚨 CRITICAL ALERT: More than 50 critical errors detected!\033[0m\n";
        }
        else if (cpu > 80.0 || errorRate > 30.0)
        {
            std::cout << "\033[1;31m● HIGH - Elevated System Metrics\033[0m\n";
        }
        else if (cpu > 50.0)
        {
            std::cout << "\033[1;33m● MEDIUM - Moderate Load\033[0m\n";
        }
        else
        {   
            std::cout << "\033[1;32m● NORMAL - System Stable\033[0m\n";
        }

        std::cout << "\n=============================================================\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}