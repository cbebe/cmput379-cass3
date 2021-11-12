// https://www.binarytides.com/server-client-example-c-sockets-linux/
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "logger.h"
#include "socket.h"
#include "util.h"

#define TIMEOUT 5

Logger* logger;
SocketServer* server;

void sighandler(int signum) {
  (void)(signum);
  logger->logSummary(*server);
  delete server;
  delete logger;
  exit(0);
}

int main(int argc, char const* argv[]) {
  checkArgc(argc, 2, argv[0]);
  signal(SIGALRM, sighandler);

  int port = std::atoi(argv[1]);
  checkPort(port);
  server = new SocketServer(port);
  logger = new Logger(port);

  while (true) {
    alarm(TIMEOUT);
    int arg = server->receiveTrans();
    logger->logRequest(server->getRequests(), arg, server->getClient());
    Trans(arg);
    logger->logDone(server->getRequests(), server->getClient());
    server->sendResponse();
  }

  return 0;
}
