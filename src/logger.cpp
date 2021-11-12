#include "logger.h"

#include <fstream>
#include <iomanip>
#include <sstream>

#include "util.h"

Logger::Logger(int port) {
  std::string filename = getHost();
  outfile.open(filename);
  outfile << "Using port " << port << std::endl;
}

Logger::Logger(int port, std::string address) : Logger(port) {
  outfile << "Using server address " << address << std::endl;
  outfile << "Host " << getHost() << std::endl;
}

Logger::~Logger() { outfile.close(); }

void Logger::logWithTime(std::string message) {
  outfile << getTime() << ": " << message << std::endl;
}

std::string strOp(const char* pre, int val) {
  std::stringstream s;
  s << pre << std::setw(3) << val << ")";
  return s.str();
}

void Logger::logSend(int val) { logWithTime(strOp("Send (T", val)); }

void Logger::logRecv(int val) { logWithTime(strOp("Recv (D", val)); }

void Logger::logSleep(int units) {
  outfile << "Sleep " << std::setw(2) << units << " units" << std::endl;
}

void Logger::logTrans(int trans) {
  outfile << "Sent " << std::setw(2) << trans << " transactions" << std::endl;
}