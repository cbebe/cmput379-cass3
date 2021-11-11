#include <stdio.h>
#include <stdlib.h>

#define MIN_PORT 5000
#define MAX_PORT 64000

void check_argc(int argc, int expected, char const *program) {
  if (argc != expected) {
    if (expected == 2) {
      fprintf(stderr, "USAGE: %s PORT\n", program);
    } else if (expected == 3) {
      fprintf(stderr, "USAGE: %s PORT IP_ADDRESS\n", program);
    }
    exit(1);
  }
}

void check_port(int port) {
  if (port < MIN_PORT || port > MAX_PORT) {
    fprintf(stderr, "Port out of range: %d, [%d, %d]\n", port, MIN_PORT,
            MAX_PORT);
    exit(1);
  }
}