#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H
#include <string>
#include <vector>

struct ProcessInfo {
    int pid;
    std::string name;
    double cpuUsage;
};

class SystemInfo {
private:
    unsigned long long prevTotalTicks = 0;
    unsigned long long prevIdleTicks = 0;
    double smoothUsage = 0.0;
public:
    double getCPUUsage();
    double getRAMUsage();
    std::vector<ProcessInfo> getProcesses();
};
#endif
