% SERVER(1) server 1.0.0
% Charles Ancheta
% November 2021

# NAME

server - receive transactions from **client**.

# SYNOPSIS

**server** _PORT_

# DESCRIPTION

**server** listens to _PORT_ for incoming requests from **client** and processes them. The messages received are in the form:

T**n** **HOSTNAME**.**PID**

where **n** is the argument for **Trans**, **HOSTNAME** is the client hostname, and **PID** is the PID of the client process.  
The **server** then sends a response in the form "D**n**" where **n** is the transaction number of the request.
This program automatically exits after 30 seconds of not receiving any requests.

# SEE ALSO

client(1)
