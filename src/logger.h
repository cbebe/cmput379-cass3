#ifndef _LOGGER_H_
#define _LOGGER_H_

FILE* init_outfile(int port);

void get_host(char* hostname_pid);
void get_time(char* time_str);
void log_send(FILE* fp, int arg);
void log_recv(FILE* fp, int trans);

#endif /* _LOGGER_H_ */
