// https://www.binarytides.com/server-client-example-c-sockets-linux/
#include <arpa/inet.h>  //inet_addr
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int main(int argc, char const *argv[]) {
  check_argc(argc, 2, argv[0]);

  int port = atoi(argv[1]);
  check_port(port);

  int socket_desc;
  struct sockaddr_in server, client;
  if ((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "Could not create socket\n");
    return 1;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  if (bind(socket_desc, &server, sizeof(server)) < 0) {
    perror("bind failed");
    return 1;
  }

  listen(socket_desc, -1);

  socklen_t sock_len = sizeof(struct sockaddr_in);
  int client_sock;
  while ((client_sock = accept(socket_desc, &client, &sock_len))) {
    char request[32], response[32];

    int read_size = recv(client_sock, request, 32, 0);
    // recv failed or client disconnected
    if (read_size == 0 || read_size == -1) continue;

    char cmd;
    int arg;
    scanf("%c%d", &cmd, &arg);
    Trans(arg);
  }

  if (client_sock < 0) {
    perror("accept failed");
    return 1;
  }
  return 0;
}
