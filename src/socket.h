#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <arpa/inet.h>
#include <sys/socket.h>

#include <chrono>
#include <string>
#include <unordered_map>

class Socket {
 public:
  Socket(int port);

 protected:
  struct sockaddr_in config;
};

class SocketServer : public Socket {
 public:
  SocketServer(int port);
  ~SocketServer();
  int receiveTrans();
  void sendResponse();
  std::string& getClient();
  int getRequests();
  std::unordered_map<std::string, int>& getClientRequests();
  double getDuration();

 private:
  std::unordered_map<std::string, int> clientRequests;
  std::string client;
  std::chrono::time_point<std::chrono::system_clock> firstReq;
  std::chrono::time_point<std::chrono::system_clock> lastReq;
  int requests;
  int serverSock;
  int clientSock;
};

class SocketClient : public Socket {
 public:
  SocketClient(int port, char const* server);
  int sendTrans(int arg);
};

#endif /* _SOCKET_CLIENT_H_ */
