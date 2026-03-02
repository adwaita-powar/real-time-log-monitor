#pragma once

class AlertManager;
class CPUMonitor;

class Dashboard 
{
public:
    void start(AlertManager& alertManager,
               CPUMonitor& cpuMonitor);

private:
    void printCPUBar(double cpuUsage);   // ✅ MATCHES .cpp
};