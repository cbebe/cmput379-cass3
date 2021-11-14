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

/**
 * @brief Source-global pointer so that the signal handler has a reference to
 * the logger
 */
Logger* logger;

/**
 * @brief Source-global pointer so that the signal handler has a reference to
 * the socket server
 */
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
    // SERVER_TIMEOUT is defined in the Makefile
    // 5 seconds by default for dev, 30 seconds in the submission target
    alarm(SERVER_TIMEOUT);
    int arg = server->receiveTrans();
    logger->logRequest(server->getRequests(), arg, server->getClient());
    Trans(arg);
    logger->logDone(server->getRequests(), server->getClient());
    server->sendResponse();
  }

  return 0;
}
