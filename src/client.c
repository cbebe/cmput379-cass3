#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "util.h"

void send_trans(int arg) {}

void run_client(int port, char const *ip_address) {
  FILE *outfile = init_outfile(port);
  fprintf(outfile, "Using server address %s\n", ip_address);
  char hostpid[512];
  get_host(hostpid);
  fprintf(outfile, "Host %s\n", hostpid);

  char cmd;
  int arg;
  int d = 0;
  int trans = 0;
  while (scanf("%c%d\n", &cmd, &arg) >= 0) {
    if (cmd == 'S') {
      fprintf(outfile, "Sleep %2d units\n", arg);
      Sleep(arg);
    } else {  // cmd == 'T'
      log_send(outfile, arg);
      ++trans;
      send_trans(arg);
      // TODO: use actual value here
      log_recv(outfile, ++d);
    }
  }

  fprintf(outfile, "Sent %2d transactions\n", trans);
  fclose(outfile);
}

int main(int argc, char const *argv[]) {
  check_argc(argc, 3, argv[0]);
  int port = atoi(argv[1]);
  check_port(port);

  run_client(port, argv[2]);

  return 0;
}
