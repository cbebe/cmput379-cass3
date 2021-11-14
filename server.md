% SERVER(1) server 1.0.0
% Charles Ancheta
% November 2021

# NAME

server - receive transactions from **client**.

# SYNOPSIS

**server** _port_

# DESCRIPTION

**server** listens to _port_ for incoming requests from **client** and processes them. The messages received are in the form:

T**n** **name**

where **n** is the argument for Trans(int), and **name** is the name of the client process. **server** then sends a response in the form "D**n**" where **n** is the transaction number of the request. **server** automatically exits after 30 seconds of not receiving any requests. The timeout value can be changed by defining SERVER_TIMEOUT in seconds.

**server** logs all requests received, responses sent, and a summary of all transactions before program termination in a log file named **hostname**.**pid**, where **hostname** is the name of the machine running **server**, and **pid** is its process ID.

# SEE ALSO

client(1)
