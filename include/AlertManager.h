#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <atomic>
#include <vector>
#include <string>

class AlertManager 
{
public:
    // ---- Metrics ----
    std::atomic<int> total{0};
    std::atomic<int> info{0};
    std::atomic<int> warning{0};
    std::atomic<int> error{0};
    std::atomic<int> critical{0};
    std::atomic<int> logsPerSecond{0};

    // ---- Alert Logic ----
    std::vector<std::string> evaluate(float cpu);
};

#endif