#include "socket.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "util.h"

/**
 * @brief Construct a new Socket:: Socket object
 *
 * @param port port number for configuration
 */
Socket::Socket(int port) {
  config.sin_family = AF_INET;
  config.sin_port = htons(port);
}

/**
 * @brief Construct a new Socket Server:: Socket Server object
 *
 * @param port port number to listen to
 */
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

/**
 * @brief Destroy the Socket Server:: Socket Server object
 *
 * Closes bound socket
 */
SocketServer::~SocketServer() { close(serverSock); }

/**
 * @brief Receive transaction from a client
 *
 * @return int transaction argument
 */
int SocketServer::receiveTrans() {
  struct sockaddr_in clientConfig;
  socklen_t sock_len = sizeof(client);
  clientSock = accept(serverSock, (struct sockaddr*)&clientConfig, &sock_len);

  if (clientSock < -1) {
    perror("accept failed");
    exit(1);
  }
  char request[1024];
  memset(request, 0, sizeof(request));
  int read_size = recv(clientSock, request, sizeof(request), 0);
  // recv failed or client disconnected
  if (read_size == 0 || read_size == -1) return -1;
  char cmd, hostname[512];
  int arg;
  std::sscanf(request, "%c%d %s", &cmd, &arg, hostname);
  client = std::string(hostname);
  if (clientRequests.find(hostname) == clientRequests.end()) {
    clientRequests[hostname] = 0;
  }
  if (requests == 0) {
    firstReq = std::chrono::system_clock::now();
  } else {
    lastReq = std::chrono::system_clock::now();
  }
  ++requests;
  ++clientRequests[hostname];

  return arg;
}

/**
 * @brief client getter
 *
 * @return std::string& hostname and PID of currently connected client
 */
std::string& SocketServer::getClient() { return client; }

/**
 * @brief requests getter
 *
 * @return int total number of requests
 */
int SocketServer::getRequests() { return requests; }

/**
 * @brief clientRequests getter
 *
 * @return std::unordered_map<std::string, int>& record of all clients
 */
std::unordered_map<std::string, int>& SocketServer::getClientRequests() {
  return clientRequests;
}

/**
 * @brief Send response to currently connected client
 */
void SocketServer::sendResponse() {
  std::string message = "D" + std::to_string(requests);
  if (send(clientSock, message.c_str(), message.length(), 0) < 0) {
    std::cerr << "send failed" << std::endl;
    return;
  }
}

/**
 * @brief Get duration between the first and last request in milliseconds
 *
 * @return double duration in milliseconds
 */
double SocketServer::getDuration() {
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(lastReq - firstReq)
          .count();

  return double(millis);
}

/**
 * @brief Construct a new Socket Client:: Socket Client object
 *
 * @param port port number of the server
 * @param server IP address of the server
 */
SocketClient::SocketClient(int port, char const* server) : Socket(port) {
  config.sin_addr.s_addr = inet_addr(server);
}

/**
 * @brief Send a transaction request to the server
 *
 * @param arg transaction argument
 * @return int transaction number received
 */
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

  if (send(sock, message.c_str(), message.length(), 0) < 0) {
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