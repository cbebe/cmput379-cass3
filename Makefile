CC=g++
SHARED_SRC := tands util logger socket
OBJ=$(SHARED_SRC:%=%.o)

# defines the duration in seconds before the server automatically exits
# after not receiving any requests (5 seconds for dev purposes)
TIMEOUT := 5
CXXFLAGS = -Wall -Wextra -Wpedantic -O -DSERVER_TIMEOUT=$(TIMEOUT)

APP := server client
MAN_OUTPUT := $(APP:%=%.pdf)

# set SERVER_TIMEOUT to 30 seconds
all: TIMEOUT := 30
all: $(APP)

pdf: $(MAN_OUTPUT)

%: %.o $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $<

%.o: src/%.c
	$(CC) $(CXXFLAGS) -o $@ -c $<

%.pdf: %.1
	groff -mandoc -Tpdf $^ >$@

clean:
	rm -f $(APP) $(MAN_OUTPUT)

# wildcard target for calling targets in development Makefile
# not included in submission :P
d-%:
	$(MAKE) -f dev.mk $*

# shhh keep it a secret babe
# https://www.youtube.com/watch?v=kverb_QNSNY
%.1: %.md
	$(MAKE) -f dev.mk $@

.PHONY: all clean pdf
