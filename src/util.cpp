#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#define MIN_PORT 5000
#define MAX_PORT 64000

#include "util.h"

/**
 * @brief Get the current time
 *
 * @return std::string the current time formatted for logging
 */
std::string getTime() {
  using namespace std::chrono;
  std::stringstream s;
  auto millis =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();

  s << std::fixed << std::setprecision(2) << double(millis) / 1000;
  return s.str();
}

/**
 * @brief Get the name of the current process defined by hostname.pid
 *
 *
 * @return std::string process name
 */
std::string getProcessName() {
  char name[255];
  gethostname(name, sizeof(name));
  return std::string(name) + "." + std::to_string(getpid());
}

/**
 * @brief Check that the program received enough arguments
 *
 * @param argc argument count
 * @param expected expected argument count
 * @param program name of program
 */
void checkArgc(int argc, int expected, char const* program) {
  if (argc == expected) return;  // ok

  if (expected == 2) {
    std::cerr << "USAGE: " << program << " PORT" << std::endl;
  } else if (expected == 3) {
    std::cerr << "USAGE: " << program << " PORT IP_ADDRESS" << std::endl;
  }
  exit(1);
}

/**
 * @brief Check that the given port argument is in the range
 *
 * @param arg the command line argument for port
 * @return int the port number
 */
int getPort(char const* arg) {
  int port = std::atoi(arg);
  if (port >= MIN_PORT && port <= MAX_PORT) return port;  // ok

  std::cerr << "Port out of range: " << port << ", [" << MIN_PORT << ", "
            << MAX_PORT << "]\n";
  exit(1);
  // never gets here
  return -1;
}