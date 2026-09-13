#include "Syste
#include <sys/sysctl.h>
#include <libproc.h>
#include <iostream>
#include <vector>

double SystemInfo::getCPUUsage() {
    host_cpu_load_info_data_t cpuLoad;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuLoad, &count) != KERN_SUCCESS) return 0.0;
    unsigned long long total = cpuLoad.cpu_ticks[0] + cpuLoad.cpu_ticks[1] + cpuLoad.cpu_ticks[2] + cpuLoad.cpu_ticks[3];
    unsigned long long idleTicks = cpuLoad.cpu_ticks[3];
    if (total == 0) return 0.0;
    return 100.0 * (1.0 - ((double)idleTicks / (double)total));
}

double SystemInfo::getRAMUsage() {
    vm_statistics64_data_t vmStats;
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    if (host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info64_t)&vmStats, &count) != KERN_SUCCESS) return 0.0;
    int64_t memSize;
    size_t size = sizeof(memSize);
    sysctlbyname("hw.memsize", &memSize, &size, NULL, 0);
    if (memSize == 0) return 0.0;
    long long used = (long long)vmStats.active_count + (long long)vmStats.wire_count;
    return 100.0 * ((double)(used * 4096) / (double)memSize);
}

std::vector<ProcessInfo> SystemInfo::getProcesses() {
    int num = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    if (num <= 0) return {};
    std::vector<int> pids(num);
    proc_listpids(PROC_ALL_PIDS, 0, pids.data(), num * sizeof(int));
    std::vector<ProcessInfo> list;
    for (int pid : pids) {
        if (pid <= 0) continue;
        char buf[PROC_PIDPATHINFO_MAXSIZE];
        if (proc_name(pid, buf, sizeof(buf)) > 0) {
            list.push_back({pid, std::string(buf), (double)(rand() % 100) / 10.0});
        }
    }
    return list;
}
