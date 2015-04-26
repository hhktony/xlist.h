CC = gcc
# CPPFLAGS = -DTAIL
CFLAGS = -Wall -W -g
TARGETS = t_xlist

all : $(TARGETS)

clean:
	$(RM) $(TARGETS) a.out *~ tags

.PHONY: all clean
