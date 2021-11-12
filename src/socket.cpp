#include "socket.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#include "util.h"

Socket::Socket(int port) {
  config.sin_family = AF_INET;
  config.sin_port = htons(port);
}

SocketServer::SocketServer(int port) : Socket(port) {
  config.sin_addr.s_addr = INADDR_ANY;
  requests = 0;
  serverSock = socket(AF_INET, SOCK_STREAM, 0);

  // ah yes, an error in a class constructor exits the whole program
  // peak software engineering
  if (serverSock == -1) {
    std::cerr << "Could not create socket" << std::endl;
    exit(1);
  }

  if (bind(serverSock, (struct sockaddr*)&config, sizeof(config)) < 0) {
    perror("bind failed");
    exit(1);
  }

  listen(serverSock, -1);
}

SocketServer::~SocketServer() { close(serverSock); }

int SocketServer::receiveTrans() {
  struct sockaddr_in client;
  socklen_t sock_len = sizeof(client);
  clientSock = accept(serverSock, (struct sockaddr*)&client, &sock_len);

  if (clientSock < -1) {
    perror("accept failed");
    exit(1);
  }
  char request[1024];

  int read_size = recv(clientSock, request, sizeof(request), 0);
  // recv failed or client disconnected
  if (read_size == 0 || read_size == -1) return -1;
  char cmd;
  int arg;
  char hostname[512];

  std::sscanf(request, "%c%d %s", &cmd, &arg, hostname);

  if (clientRequests.find(hostname) == clientRequests.end()) {
    clientRequests[hostname] = 0;
  }

  ++requests;
  ++clientRequests[hostname];

  return arg;
}

void SocketServer::sendResponse() {
  std::string message = "D" + std::to_string(requests);
  if (send(clientSock, message.c_str(), message.size(), 0) < 0) {
    std::cerr << "send failed" << std::endl;
    return;
  }
}

SocketClient::SocketClient(int port, char const* server) : Socket(port) {
  config.sin_addr.s_addr = inet_addr(server);
}

int SocketClient::sendTrans(int arg) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Could not create socket" << std::endl;
    return -1;
  }

  if (connect(sock, (struct sockaddr*)&config, sizeof(config)) < 0) {
    perror("connect failed");
    return -1;
  }

  std::string message = "T" + std::to_string(arg) + " " + getHost();

  if (send(sock, message.c_str(), message.size(), 0) < 0) {
    std::cerr << "send failed" << std::endl;
    return -1;
  }

  char response[64];

  if (recv(sock, response, sizeof(response), 0) < 0) {
    std::cerr << "recv failed" << std::endl;
    return -1;
  }

  close(sock);

  int trans;
  std::sscanf(response, "D%d", &trans);
  return trans;
}