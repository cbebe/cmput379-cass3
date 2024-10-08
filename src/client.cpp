#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "logger.h"
#include "socket.h"
#include "util.h"

int main(int argc, char const *argv[]) {
  checkArgc(argc, 3, argv[0]);
  int port = getPort(argv[1]);
  Logger logger(port, argv[2]);
  SocketClient client(port, argv[2]);

  char cmd;
  int arg;
  int trans = 0;
  while (std::scanf("%c%d\n", &cmd, &arg) >= 0) {
    if (cmd == 'S') {
      logger.logSleep(arg);
      Sleep(arg);
    } else if (cmd == 'T') {
      logger.logSend(arg);
      ++trans;
      int transNumber = client.sendTrans(arg);
      if (transNumber < 0) break;  // there was an error
      logger.logRecv(transNumber);
    } else {
      std::cerr << "Bad input, ignoring: " << cmd << " " << arg << std::endl;
    }
  }

  logger.logSummary(trans);

  return 0;
}
