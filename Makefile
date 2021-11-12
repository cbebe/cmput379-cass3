CC=g++
SHARED_SRC := tands util logger
OBJ=$(SHARED_SRC:%=%.o)

CXXFLAGS := -Wall -Wextra -Wpedantic
LDFLAGS := -lpthread

APP := server client

all: clean $(APP)

%: %.o $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# wildcard target for C++ source files
%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

# wildcard target for C source files (tands)
%.o: src/%.c
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

# create example inputs
input:
	echo "T1\nT20\nT500\nT1\nT1\nT1\nT10\nT10\nS50\nT60\nT1\nT1\nS20\nT1S1\nT50\nT1" > client.in.1
	echo "T100\nT1\nT2\nT3\nT4\nS75\nT5\nT6\nT7\nT8\nT9\nT1\nT1\nT1\nT1\nT1" > client.in.2

clean:
	rm -f $(APP)
# remove output logs
	rm -f $(shell hostname).*
# remove example inputs
	rm -f client.in.*

.PHONY: all input clean
