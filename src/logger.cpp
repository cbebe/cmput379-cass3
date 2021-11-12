#include "logger.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <unordered_map>

#include "util.h"

Logger::Logger(int port) {
  std::string filename = getHost();
  outfile.open(filename);
  outfile << "Using port " << port << std::endl;
}

Logger::Logger(int port, const std::string& address) : Logger(port) {
  outfile << "Using server address " << address << std::endl;
  outfile << "Host " << getHost() << std::endl;
}

Logger::~Logger() { outfile.close(); }

void Logger::logWithTime(const std::string& message) {
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

std::string reqOp(int trans, const std::string& message,
                  const std::string& client) {
  std::stringstream s;
  s << "#" << std::setw(3) << trans << " " << message << " from " << client;
  return s.str();
}

void Logger::logRequest(int trans, int arg, const std::string& client) {
  logWithTime(reqOp(trans, strOp("(T", arg), client));
}

void Logger::logDone(int trans, const std::string& client) {
  logWithTime(reqOp(trans, "(Done)", client));
}

std::string transactions(int trans, const std::string& client) {
  std::stringstream s;
  s << std::setw(4) << trans << " transactions from " << client;
  return s.str();
}

void Logger::logSummary(SocketServer& server) {
  outfile << std::endl << "SUMMARY" << std::endl;

  for (auto& it : server.getClientRequests()) {
    outfile << transactions(it.second, it.first) << std::endl;
  }

  int requests = server.getRequests();
  double duration = server.getDuration() / 1000;
  double throughput = requests != 0 ? double(requests) / duration : 0;

  outfile << std::setw(4) << std::fixed << std::setprecision(1) << throughput
          << " transactions/sec  (" << requests << "/" << std::setprecision(2)
          << duration << ")" << std::endl;
}