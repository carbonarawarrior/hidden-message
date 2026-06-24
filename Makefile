CMD = "cmd"
PASS = "found"
MESSAGE = "A secret message!\n"
.PHONY: install clean

$(CMD):
	gcc -Os hidden.c -o $(CMD) -DCMD=\"$(CMD)\" -DPASS=\"$(PASS)\" -DMESSAGE=\"$(MESSAGE)\"

install: $(CMD)
	cp ./$(CMD) /usr/bin
	chmod 755 /usr/bin/$(CMD)
clean:
	rm -f $(CMD)
