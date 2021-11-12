#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <chrono>
#include <fstream>
#include <unordered_map>

#include "socket.h"

class Logger {
 public:
  Logger(int port);
  Logger(int port, const std::string& address);
  ~Logger();
  void logSend(int arg);
  void logRecv(int trans);
  void logSleep(int units);
  void logTrans(int trans);
  void logRequest(int trans, int arg, const std::string& client);
  void logDone(int trans, const std::string& client);
  void logSummary(SocketServer& server);

 private:
  std::ofstream outfile;
  void logWithTime(const std::string& message);
  std::chrono::time_point<std::chrono::system_clock> firstLog;
  bool first;
};

#endif /* _LOGGER_H_ */
