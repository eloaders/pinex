#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "mem_info.h"

double getMemoryUsage(){
    FILE* file;
    unsigned long long memtotal, memfree, memavailable, buffers, cached;

    file = fopen("/proc/meminfo", "r");
    fscanf(file, "MemTotal: %llu kB MemFree: %llu kB MemAvailable: %llu kB Buffers: %llu kB Cached: %llu kB",
           &memtotal, &memfree, &memavailable, &buffers, &cached);
    fclose(file);

    double result = (memtotal - (memfree + buffers + cached));

    return result;
}

double getMemoryTotal(){
    FILE* file;
    unsigned long long memtotal;
    file = fopen("/proc/meminfo", "r");
    fscanf(file, "MemTotal: %llu kB",&memtotal);
    fclose(file);
    return memtotal;
}

double getMemoryPercentage(){
    FILE* file;
    double percentage;
    int memory_used;
    //int memory_free;
    unsigned long long memtotal, memfree, memavailable, buffers, cached;

    file = fopen("/proc/meminfo", "r");
    fscanf(file, "MemTotal: %llu kB MemFree: %llu kB MemAvailable: %llu kB Buffers: %llu kB Cached: %llu kB",
           &memtotal, &memfree, &memavailable, &buffers, &cached);
    fclose(file);

    memory_used = memtotal - memfree - cached - buffers;
    //memory_free = memtotal - memory_used;

    percentage = memory_used * 100 / memtotal;

    return percentage;

}

