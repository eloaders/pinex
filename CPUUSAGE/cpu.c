#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "cpu.h"

double cpu_usage;	/* (working time) / (working time + idle time) * 100 */
static int NR_CPU;
static FILE *fin;
static pthread_t readcpu_thread;

static void threaded_read_cpu (void)
{
	double	s[4], t[4];

	if ((fin = fopen ("/proc/stat", "r")) == NULL)
		printf("failed to open /proc/stat");
	fscanf (fin, "%*s %lf %lf %lf %lf", &s[0], &s[1], &s[2], &s[3]);
	fclose (fin);
	usleep (CPU_INT);
	if ((fin = fopen ("/proc/stat", "r")) == NULL)
		printf("failed to open /proc/stat");
	fscanf (fin, "%*s %lf %lf %lf %lf", &t[0], &t[1], &t[2], &t[3]);
	fclose (fin);
	cpu_usage = ((t[0] + t[1] + t[2]) - (s[0] + s[1] + s[2])) /
		((t[0] + t[1] + t[2] + t[3]) - (s[0] + s[1] + s[2] + s[3])) *
		100.0;
}

void read_cpu (void)
{
	if (pthread_create (&readcpu_thread, NULL, (void *(*)(void *)) &threaded_read_cpu, NULL) != 0)
		printf("failed to create thread for calculating cpu usage");
	pthread_detach (readcpu_thread);
}

void readcpu_fin (void)
{
	pthread_cancel (readcpu_thread);
	pthread_join (readcpu_thread, NULL);
	fclose (fin);
}