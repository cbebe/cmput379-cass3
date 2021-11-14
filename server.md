% SERVER(1) server 1.0.0
% Charles Ancheta
% November 2021

# NAME

server - receive transactions from **client**.

# SYNOPSIS

**server** _port_

# DESCRIPTION

**server** listens to _port_ for incoming requests from **client** and processes them. The messages received are in the form:

T**n** **hostname**.**pid**

where **n** is the argument for **Trans**, **hostname** is the client hostname, and **pid** is the PID of the client process. **server** then sends a response in the form "D**n**" where **n** is the transaction number of the request. **server** automatically exits after 30 seconds of not receiving any requests and prints a summary of the transactions received.

# SEE ALSO

client(1)
