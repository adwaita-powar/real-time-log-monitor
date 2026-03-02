#include "../include/LogGenerator.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>

static std::string timestamp() 
{
    auto now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%b %d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

void LogGenerator::start(AlertManager& alertManager)
{
    std::ofstream file("engine.log");

    std::vector<std::string> logs;
    // Generate 5000 logs total

    for(int i=0;i<3000;i++)
      logs.push_back("INFO: Started service.");

    for(int i=0;i<800;i++)
      logs.push_back("WARNING: deprecated API usage");

    for(int i=0;i<900;i++)
      logs.push_back("ERROR: device initialization failed");

    for(int i=0;i<300;i++)
      logs.push_back("CRITICAL: kernel panic detected");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(logs.begin(), logs.end(), gen);

    int counter = 0;
    auto lastTime = std::chrono::steady_clock::now();

    for(const auto& msg : logs)
    {
        file << timestamp() << " ubuntu " << msg << std::endl;
        file.flush();

        // Update counters
        // Update total logs FIRST
        alertManager.total++;

        // Update counters
        if (msg.find("CRITICAL") != std::string::npos)
          alertManager.critical++;
        else if (msg.find("ERROR") != std::string::npos)
          alertManager.error++;
        else if (msg.find("WARNING") != std::string::npos)
          alertManager.warning++;
        else
          alertManager.info++;        

        counter++;

        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);

        if (duration.count() >= 1)
        {
            alertManager.logsPerSecond = counter;
            counter = 0;
            lastTime = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}