#include <cstdio>
#include <cstdlib>
#include <iomanip>

#include "logger.h"
#include "socket.h"
#include "util.h"

int main(int argc, char const *argv[]) {
  checkArgc(argc, 3, argv[0]);
  int port = std::atoi(argv[1]);
  checkPort(port);

  Logger logger(port, argv[2]);
  SocketClient client(port, argv[2]);

  char cmd;
  int arg;
  int trans = 0;
  while (std::scanf("%c%d\n", &cmd, &arg) >= 0) {
    if (cmd == 'S') {
      logger.logSleep(arg);
      Sleep(arg);
    } else {  // cmd == 'T'
      logger.logSend(arg);
      ++trans;
      logger.logRecv(client.sendTrans(arg));
    }
  }

  logger.logTrans(trans);

  return 0;
}
