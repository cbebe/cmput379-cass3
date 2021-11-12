#include "logger.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <unordered_map>

#include "util.h"

/**
 * @brief Construct a new Logger:: Logger object
 *
 * Used by the server
 *
 * @param port port number of the server
 */
Logger::Logger(int port) {
  std::string filename = getHost();
  outfile.open(filename);
  outfile << "Using port " << port << std::endl;
}

/**
 * @brief Construct a new Logger:: Logger object
 *
 * Used by the client
 *
 * @param port port number of the server
 * @param address address of the server
 */
Logger::Logger(int port, const std::string& address) : Logger(port) {
  outfile << "Using server address " << address << std::endl;
  outfile << "Host " << getHost() << std::endl;
}

/**
 * @brief Destroy the Logger:: Logger object
 *
 * Closes the output file
 */
Logger::~Logger() { outfile.close(); }

/**
 * @brief Logs output to the file including the UNIX timestamp
 *
 * @param message message to log to the file
 */
void Logger::logWithTime(const std::string& message) {
  outfile << getTime() << ": " << message << std::endl;
}

/**
 * @brief Create an operation string
 *
 * @param pre prefix to add
 * @param val value to enclose
 * @return std::string message to log
 */
std::string strOp(const char* pre, int val) {
  std::stringstream s;
  s << pre << std::setw(3) << val << ")";
  return s.str();
}

/**
 * @brief Log a send event
 *
 * @param arg transaction argument to send
 */
void Logger::logSend(int arg) { logWithTime(strOp("Send (T", arg)); }

/**
 * @brief Log a recv event
 *
 * @param trans transaction number received
 */
void Logger::logRecv(int trans) { logWithTime(strOp("Recv (D", trans)); }

/**
 * @brief Log a sleep event
 *
 * @param units units to sleep
 */
void Logger::logSleep(int units) {
  outfile << "Sleep " << std::setw(2) << units << " units" << std::endl;
}

/**
 * @brief Log a client summary
 *
 * @param trans number of transactions sent
 */
void Logger::logSummary(int trans) {
  outfile << "Sent " << std::setw(2) << trans << " transactions" << std::endl;
}

/**
 * @brief Create server operation message
 *
 * @param trans transaction number
 * @param event event message (either transaction or done)
 * @param client hostname of client
 * @return std::string message for logging
 */
std::string reqOp(int trans, const std::string& event,
                  const std::string& client) {
  std::stringstream s;
  s << "#" << std::setw(3) << trans << " " << event << " from " << client;
  return s.str();
}

/**
 * @brief Log a transaction request
 *
 * Used by the server
 *
 * @param trans transaction number
 * @param arg transaction argument
 * @param client hostname of client
 */
void Logger::logRequest(int trans, int arg, const std::string& client) {
  logWithTime(reqOp(trans, strOp("(T", arg), client));
}

/**
 * @brief Log a done event
 *
 * Used by the server
 *
 * @param trans transaction number
 * @param client hostname of client
 */
void Logger::logDone(int trans, const std::string& client) {
  logWithTime(reqOp(trans, "(Done)", client));
}

/**
 * @brief Get total transactions from a client for summary
 *
 * @param trans transaction number
 * @param client hostname of client
 * @return std::string message for logging
 */
std::string transactions(int trans, const std::string& client) {
  std::stringstream s;
  s << std::setw(4) << trans << " transactions from " << client;
  return s.str();
}

/**
 * @brief Logs the summary of a SocketServer
 *
 * @param server SocketServer object to log summary of
 */
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