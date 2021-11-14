# CMPUT 379 Assignment 3 - Client-Server

Charles Ancheta - cancheta

## Compilation

Run `make` to compile `server` and `client` (with `-O` flag by default).
Run `make pdf` to create PDF versions of the man pages for `server` and `client` using `groff`.

## Files

### `tands.c`

Provided file containing functions `Trans(int)` and `Sleep(int)`.

- `void Trans(int n)` - Simulate a transaction with the parameter n (n > 0) determining the duration of the transaction.

- `void Sleep(int n)` - Simulate waiting for new input by sleeping for n \* 10 milliseconds

### `logger.cpp`

Contains the implementation of the `Logger` class, used by the `server` and `client` for logging.

### `socket.cpp`

Contains the implementation of the `Socket` class, and its child classes `ServerSocket` and `ClientSocket`. These classes are used for communicating with `server`s and `client`s through sockets.

### `util.cpp`

Contains utility functions such as getting the host or getting the current UNIX timestamp. Also contains functions for validating command line arguments.

### `client.cpp`

Main file for the `client` program.

### `server.cpp`

Main file for the `server` program.

## Assumptions

The Makefile assumes that the executables are compiled with the `all` target, which sets the SERVER_TIMEOUT variable to 30 seconds and is the default target for `make`. Compiling with `make server` will leave the SERVER_TIMEOUT variable with the default value of 5 seconds.
`client` assumes that there is a running `server` for the duration that the `client` is running and that the provided port and IP address are correct. Otherwise, it will freeze on a host that is not found, or immediately exit on an unfinished transaction.

## Solution Approach

Looking at the server's example output, I realized that the server needs to keep track of the client names and the number of transactions from each client. I initially thought of implementing my own hash table in C but found that too hard, forcing me to use C++ just for the `unordered_map` container :(  
Another problem I found was accepting requests from multiple clients at once. Once the server accepts a connection, it can only send messages to and from that one connection. I solved this by creating a new connection every time a client sends a transaction and disconnecting after it receives a response from the server. This may have slightly affected the performance of the programs.  
Another specification for the server is to exit after receiving no requests for 30 seconds. I initially thought of using poll or select to time out the connection but found that too complicated. I ended up using a SIGALRM handler and resetting the alarm back to 30 seconds every time a new connection is received.
