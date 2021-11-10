SHARED_SRC := tands
OBJ=$(SHARED_SRC:%=%.o)

CFLAGS := -Wall -Wextra -Wpedantic
LDFLAGS := -lpthread

APP := server client

all: $(APP)

%: %.o $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: src/%.c
	gcc $(CFLAGS) -o $@ -c $< $(LDFLAGS)

build:
	mkdir $@

clean:
	rm -f $(APP)

.PHONY: all
