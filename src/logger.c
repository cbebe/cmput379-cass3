#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void get_host(char* hostname_pid) {
  pid_t pid = getpid();
  char name[255];
  gethostname(name, 255);
  sprintf(hostname_pid, "%s.%d", name, pid);
}

FILE* init_outfile(int port) {
  char filename[512];
  get_host(filename);
  FILE* outfile = fopen(filename, "w");

  fprintf(outfile, "Using port %d\n", port);

  return outfile;
}

void get_time(char* time_str) {
  struct timeval now;
  gettimeofday(&now, NULL);
  sprintf(time_str, "%ld.%02ld", now.tv_sec, now.tv_usec / 10000);
}

void log_with_time(FILE* fp, char* msg) {
  char time[16];
  get_time(time);
  fprintf(fp, "%s: %s\n", time, msg);
}

void log_send(FILE* fp, int arg) {
  char buf[16];
  sprintf(buf, "Send (T%3d)", arg);
  log_with_time(fp, buf);
}

void log_recv(FILE* fp, int trans) {
  char buf[16];
  sprintf(buf, "Recv (D%3d)", trans);
  log_with_time(fp, buf);
}