#include <unistd.h>

#include <chrono>
#include <iomanip>
#include <iostream>

#define MIN_PORT 5000
#define MAX_PORT 64000

#include "util.h"

std::string getTime() {
  using namespace std::chrono;
  std::stringstream s;
  auto millis =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();

  s << std::fixed << std::setprecision(2) << double(millis) / 1000;
  return s.str();
}

std::string getHost() {
  char name[255];
  gethostname(name, sizeof(name));
  return std::string(name) + "." + std::to_string(getpid());
}

void checkArgc(int argc, int expected, char const *program) {
  if (argc == expected) return;  // ok

  if (expected == 2) {
    std::cerr << "USAGE: " << program << " PORT" << std::endl;
  } else if (expected == 3) {
    std::cerr << "USAGE: " << program << " PORT IP_ADDRESS" << std::endl;
  }
  exit(1);
}

void checkPort(int port) {
  if (port >= MIN_PORT && port <= MAX_PORT) return;  // ok

  std::cerr << "Port out of range: " << port << ", [" << MIN_PORT << ", "
            << MAX_PORT << "]\n";
  exit(1);
}