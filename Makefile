CC = gcc
# CPPFLAGS = -DTAIL
CFLAGS = -Wall -W -g
LDFLAGS =
TARGETS = test

all : test

clean:
	$(RM) $(TARGETS) a.out *~ tags

.PHONY: all clean
