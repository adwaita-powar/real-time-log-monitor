
#include "../include/AlertManager.h"

std::vector<std::string> AlertManager::evaluate(float cpu)
{
    std::vector<std::string> alerts;

    if (cpu > 90)
    {
        alerts.push_back(
            "!!! HIGH CPU USAGE DETECTED !!!\n"
            "System resources are under heavy load.");
    }

    if (critical.load() > 50)
    {
        alerts.push_back(
            "!!! CRITICAL LOG SPIKE DETECTED !!!\n"
            "Immediate investigation required.");
    }

    return alerts;
}