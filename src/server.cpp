// https://www.binarytides.com/server-client-example-c-sockets-linux/
#include <arpa/inet.h>  //inet_addr

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "logger.h"
#include "socket.h"
#include "util.h"

int main(int argc, char const *argv[]) {
  checkArgc(argc, 2, argv[0]);

  int port = std::atoi(argv[1]);
  checkPort(port);
  SocketServer server(port);
  Logger logger(port);

  while (true) {
    int arg = server.receiveTrans();
    Trans(arg);
    server.sendResponse();
  }

  return 0;
}
