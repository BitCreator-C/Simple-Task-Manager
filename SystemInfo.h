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
public:
    double getCPUUsage();
    double getRAMUsage();
    std::vector<ProcessInfo> getProcesses();
};
#endif
