CC := ./cc
LD := ./ld

CFLAGS := -Wall -g -Os

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

# Build and link hello (fle)
hello: $(OBJS) tools
	$(LD) $(SRCS:.c=.fle) -o $@

%.o: %.c tools
	$(CC) $(CFLAGS) $< -o $@

# fle.py is all the binutils!
tools:
	@ln -f -s ../fle.cpp cc
	@ln -f -s ../fle.cpp ld
	@ln -f -s ../fle.cpp exec
	@ln -f -s ../fle.cpp objdump
	@ln -f -s ../fle.cpp readfle
	@ln -f -s ../fle.cpp nm

clean:
	rm -f $(OBJS) $(SRCS:.c=.fle) cc ld exec exec objdump readfle nm hello

.PHONY: all clean tools
