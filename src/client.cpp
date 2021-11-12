#include <cstdio>
#include <cstdlib>
#include <iomanip>

#include "logger.h"
#include "util.h"

void send_trans(int arg) {}

void run_client(int port, char const *ip_address) {
  Logger logger(port);
  logger.logClient(ip_address);

  char cmd;
  int arg;
  int d = 0;
  int trans = 0;
  while (std::scanf("%c%d\n", &cmd, &arg) >= 0) {
    if (cmd == 'S') {
      logger.outfile << "Sleep " << std::setw(2) << arg << " units"
                     << std::endl;
      Sleep(arg);
    } else {  // cmd == 'T'
      logger.logSend(arg);
      ++trans;
      send_trans(arg);
      // TODO: use actual value here
      logger.logRecv(++d);
    }
  }

  logger.outfile << "Sent " << std::setw(2) << " transactions" << std::endl;
}

int main(int argc, char const *argv[]) {
  checkArgc(argc, 3, argv[0]);
  int port = std::atoi(argv[1]);
  checkPort(port);

  run_client(port, argv[2]);

  return 0;
}
