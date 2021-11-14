###############################
#         DEV TARGETS         #
###############################

MAN := client.1 server.1
LOCAL_MAN := $(MAN:%=/usr/local/man/man1/%)
LOCAL_MAN_GZ := $(LOCAL_MAN:%=%.gz)
SUBMISSION_TAR := Assignment3.tar.gz

IP := 127.0.0.1

%: 
	$(MAKE) $@

# create example inputs
client.in.1:
	echo "T1\nT20\nT500\nT1\nT1\nT1\nT10\nT10\nS50\nT60\nT1\nT1\nS20\nT1S1\nT50\nT1" > $@
client.in.2:
	echo "T100\nT1\nT2\nT3\nT4\nS75\nT5\nT6\nT7\nT8\nT9\nT1\nT1\nT1\nT1\nT1" > $@

clean:
	$(MAKE) clean
# remove output logs
	rm -f $(shell hostname).*
# remove example inputs
	rm -f client.in.*
# remove man outputs
	rm -f $(MAN)
	rm -f ip

man: $(LOCAL_MAN_GZ)
	sudo mandb

keep: $(MAN)

clean-man:
	sudo rm -f $^
	sudo mandb

%.1.gz: %.1
	sudo gzip -f $^

/usr/local/man/man1/%.1: %.1
	sudo cp $^ $@ 
	rm $<

# convert markdown to troff using pandoc because
# I am Just TOO SMART to Learn Anything
# https://www.youtube.com/watch?v=2xl56IJGKwY
# remove pandoc comment using tail
%.1: %.md
	pandoc $< -s -t man | tail -n +3 > $@

# run locally
run: run-server run-clients

run-server: server ip
	./server 5000 &

run-clients: client client.in.1 client.in.2
	./client 5000 $(IP) <client.in.1 &
	./client 5000 $(IP) <client.in.2 &

submit: $(SUBMISSION_TAR) clean

$(SUBMISSION_TAR): src $(MAN) README Makefile
	tar czf $@ $^


# connect clients to a remote server
remote: IP = $(shell cat ip 2>/dev/null || echo "127.0.0.1")
remote: client run-clients

# get server IP address
ip:
	echo $(shell curl ifconfig.me) > $@

.PHONY: run man keep run-clients run-server submit dev