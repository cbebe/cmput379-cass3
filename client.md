% CLIENT(1) client 1.0.0
% Charles Ancheta
% November 2021

# NAME

client - send transactions to **server**.

# SYNOPSIS

**client** _port_ _ip-address_

# DESCRIPTION

**client** sends transactions to a socket server with the given _ip-address_ and _port_.
**client** processes input from stdin and exits when it reaches the input EOF (finishing reading from a file or ^D from the keyboard). The input processed is in the form of the following two commands:

T**n**: where **n** > 0 - sends a transaction to the server  
S**n**: where 0 < **n** < 100 - sleeps with the given time in milliseconds

**client** then prints the total number of transactions sent before exiting.

# SEE ALSO

server(1)
