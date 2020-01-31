/*
 * A daemon that reads the /proc/stats file, calculates the cpu usage
 * percentage and writes it to syslog.
 *
 * Copyright (C) 2015-2016 Sebastian Glinski <sebastian.glinski@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define STAT_FILE "/proc/stat"
#define READ_SIZE 200

typedef struct {
  u_int32_t user;         /* Time spent in user mode */
  u_int32_t nice;         /* Time spent in user mode with low priority (nice) */
  u_int32_t systm;        /* Time spent in system mode */
  u_int32_t idle;         /* Time spent in the idle task */
  u_int32_t iowait;       /* Time waiting for I/O to complete */
  u_int32_t irq;          /* Time servicing interrupts */
  u_int32_t softirq;      /* Time servicing softirqs */
  u_int32_t steal;        /* Stolen time, which is the time spent in other operating systems when running in a virtualized environment */
  u_int32_t guest;        /* Time spent running a virtual CPU for guest operating systems under the control of the Linux kernel */
  u_int32_t guest_nice;   /* Time spent running a niced guest */
} cpu_stats;

cpu_stats cur_stat, pre_stat;

void read_stats_file(void);
cpu_stats read_cpu_stats(char[]);
float calculate_percentage(void);

int main(int argc, char const *argv[]) {
  while(1) {
    read_stats_file();
    printf("CPU Percentage: %f\n", calculate_percentage());
    usleep(10 * 500000); // s * microseconds
  }
  return 0;
}

double getCurrentValue(){
    double percent;
	read_stats_file();
	percent = calculate_percentage();
    return percent;
}

void read_stats_file(void) {
  FILE *file;
  file = fopen(STAT_FILE, "r");
  char puffer[READ_SIZE];

  fgets(puffer, READ_SIZE, file);

  pre_stat = cur_stat;
  cur_stat = read_cpu_stats(puffer);

  fclose(file);
}

cpu_stats read_cpu_stats(char c[]) {
  cpu_stats s;
  char *tokens[15];
  char *t;
  int i = 0;

  strtok(c, " ");

  t = strtok(NULL, " ");
  while(t != NULL) {
    sscanf(t, "%u", &((u_int32_t*)&s)[i]);
    t = strtok(NULL, " ");
    i++;
  }

  return s;
}

float calculate_percentage(void) {
  u_int32_t prevIdle = pre_stat.idle + pre_stat.iowait;
  u_int32_t idle = cur_stat.idle + cur_stat.iowait;

  u_int32_t prevNonIdle = pre_stat.user + pre_stat.nice + pre_stat.systm + pre_stat.irq + pre_stat.softirq + pre_stat.steal;
  u_int32_t nonIdle = cur_stat.user + cur_stat.nice + cur_stat.systm + cur_stat.irq + cur_stat.softirq + cur_stat.steal;

  u_int32_t totald = (idle + nonIdle) - (prevIdle + prevNonIdle);
  u_int32_t idled = idle - prevIdle;

  /* float CPU_Percentage = (totald - idled)/(float)totald; */

  return ((totald - idled) / (float)totald)*100;
}