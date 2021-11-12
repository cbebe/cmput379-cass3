#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>

class Logger {
 public:
  Logger(int port);
  Logger(int port, std::string address);
  ~Logger();
  void logSend(int arg);
  void logRecv(int trans);
  void logClient(std::string address);
  void logSleep(int units);
  void logTrans(int trans);
  std::ofstream outfile;

 private:
  void logWithTime(std::string message);
};

#endif /* _LOGGER_H_ */
