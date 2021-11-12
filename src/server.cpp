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

#define TIMEOUT 30

Logger* logger;
SocketServer* server;

/**
 * @brief Handler for timeout. Prints summary and closes logfile
 *
 * @param signum unused
 */
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
  int port = getPort(argv[1]);
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
