CC=g++
SHARED_SRC := tands util logger socket
OBJ=$(SHARED_SRC:%=%.o)

CXXFLAGS := -Wall -Wextra -Wpedantic -O

APP := server client
MAN := $(APP:%=%.1)
LOCAL_MAN := $(MAN:%=/usr/local/man/man1/%)
LOCAL_MAN_GZ := $(LOCAL_MAN:%=%.gz)

IP := 127.0.0.1

all: clean input $(APP)

%: %.o $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

# wildcard target for C++ source files
%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $<

# wildcard target for C source files (tands)
%.o: src/%.c
	$(CC) $(CXXFLAGS) -o $@ -c $<

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
# remove man outputs
	rm -f $(MAN)

man: $(LOCAL_MAN_GZ)
	sudo mandb

keep: $(MAN)

clean-man: $(LOCAL_MAN_GZ)
	sudo rm -f $^
	sudo mandb

%.1.gz: %.1
	sudo gzip -f $^

/usr/local/man/man1/%.1: %.1
	sudo cp $^ $@ 
	rm $<

# convert markdown to troff using pandoc
# remove pandoc comment using sed
%.1: %.md
	pandoc $< -s -t man | tail -n +3 > $@

# run locally
run: run-server run-clients

run-server: server ip
	./server 5000 &

run-clients:
	./client 5000 $(IP) <client.in.1 &
	./client 5000 $(IP) <client.in.2 &

# connect clients to a remote server
remote: IP = $(shell cat ip 2>/dev/null || echo "127.0.0.1")
remote: client run-clients

# get server IP address
ip:
	echo $(shell curl ifconfig.me) > $@

.PHONY: all input clean run man keep run-clients run-server
