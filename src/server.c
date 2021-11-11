#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int main(int argc, char const *argv[]) {
  check_argc(argc, 2, argv[0]);

  int port = atoi(argv[1]);
  check_port(port);

  return 0;
}
