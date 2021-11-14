#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <chrono>
#include <fstream>
#include <unordered_map>

#include "socket.h"

class Logger {
 public:
  /**
   * @brief Construct a new Logger:: Logger object
   *
   * Used by the server
   *
   * @param port port number of the server
   */
  Logger(int port);

  /**
   * @brief Construct a new Logger:: Logger object
   *
   * Used by the client
   *
   * @param port port number of the server
   * @param address address of the server
   */
  Logger(int port, const std::string& address);

  /**
   * @brief Destroy the Logger:: Logger object
   *
   * Closes the output file
   */
  ~Logger();

  /**
   * @brief Log a send event
   *
   * @param arg transaction argument to send
   */
  void logSend(int arg);

  /**
   * @brief Log a recv event
   *
   * @param trans transaction number received
   */
  void logRecv(int trans);

  /**
   * @brief Log a sleep event
   *
   * @param units units to sleep
   */
  void logSleep(int units);

  /**
   * @brief Log a transaction request
   *
   * Used by the server
   *
   * @param trans transaction number
   * @param arg transaction argument
   * @param client hostname of client
   */
  void logRequest(int trans, int arg, const std::string& client);

  /**
   * @brief Log a done event
   *
   * Used by the server
   *
   * @param trans transaction number
   * @param client hostname of client
   */
  void logDone(int trans, const std::string& client);

  /**
   * @brief Log a client summary
   *
   * @param trans number of transactions sent
   */
  void logSummary(int trans);

  /**
   * @brief Logs the summary of a SocketServer
   *
   * @param server SocketServer object to log summary of
   */
  void logSummary(SocketServer& server);

 private:
  /**
   * @brief Logs output to the file including the UNIX timestamp
   *
   * @param message message to log to the file
   */
  void logWithTime(const std::string& message);

  /**
   * @brief File stream of the log file
   */
  std::ofstream outfile;
};

#endif /* _LOGGER_H_ */
