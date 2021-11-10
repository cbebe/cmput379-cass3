#include <stdio.h>
#include <stdlib.h>

#define MIN_PORT 5000
#define MAX_PORT 64000

void Sleep(int n);

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "USAGE: %s PORT IP_ADDRESS", argv[0]);
    exit(1);
  }

  int port = atoi(argv[1]);
  if (port < MIN_PORT || port > MAX_PORT) {
    fprintf(stderr, "Port out of range: %d, [%d, %d]", port, MIN_PORT,
            MAX_PORT);
    exit(1);
  }

  return 0;
}
