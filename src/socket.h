#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <arpa/inet.h>
#include <sys/socket.h>

#include <chrono>
#include <string>
#include <unordered_map>

class Socket {
 public:
  /**
   * @brief Construct a new Socket:: Socket object
   *
   * @param port port number for configuration
   */
  Socket(int port);

 protected:
  /**
   * @brief Config for socket address
   */
  struct sockaddr_in config;
};

class SocketServer : public Socket {
 public:
  /**
   * @brief Construct a new Socket Server:: Socket Server object
   *
   * @param port port number to listen to
   */
  SocketServer(int port);

  /**
   * @brief Destroy the Socket Server:: Socket Server object
   *
   * Closes bound socket
   */
  ~SocketServer();

  /**
   * @brief Receive transaction from a client
   *
   * @return int transaction argument
   */
  int receiveTrans();

  /**
   * @brief Send response to currently connected client
   */
  void sendResponse();

  /**
   * @brief client getter
   *
   * @return std::string& hostname and PID of currently connected client
   */
  std::string& getClient();

  /**
   * @brief requests getter
   *
   * @return int total number of requests
   */
  int getRequests();

  /**
   * @brief clientRequests getter
   *
   * @return std::unordered_map<std::string, int>& record of all clients
   */
  std::unordered_map<std::string, int>& getClientRequests();

  /**
   * @brief Get duration between the first and last request in milliseconds
   *
   * @return double duration in milliseconds
   */
  double getDuration();

 private:
  /**
   * @brief Clients' names mapped to number of requests
   */
  std::unordered_map<std::string, int> clientRequests;

  /**
   * @brief Hostname and PID of the most recent client
   */
  std::string client;

  /**
   * @brief Time point of the first request since program startup
   */
  std::chrono::time_point<std::chrono::system_clock> firstReq;

  /**
   * @brief Time point of the most recent request
   */
  std::chrono::time_point<std::chrono::system_clock> lastReq;

  /**
   * @brief Total number of requests received from clients
   */
  int requests;
  /**
   * @brief File descriptor of the server socket
   */
  int serverSock;
  /**
   * @brief File descriptor of the most recent client socket
   */
  int clientSock;
};

class SocketClient : public Socket {
 public:
  /**
   * @brief Construct a new Socket Client:: Socket Client object
   *
   * @param port port number of the server
   * @param server IP address of the server
   */
  SocketClient(int port, char const* server);

  /**
   * @brief Send a transaction request to the server
   *
   * @param arg transaction argument
   * @return int transaction number received
   */
  int sendTrans(int arg);
};

#endif /* _SOCKET_CLIENT_H_ */
