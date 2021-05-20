#
# Makefile
#
# Computer Science 50
# Problem Set 6
#

# compiler to use
CC = clang

# flags to pass to the compiler
CFLAGS = -O3 -Qunused-arguments -std=c11 -Wall -Werror

# name for the executable 
EXE = server

# space-separated list of header files
HDRS = staff_func.h perso_func.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lm

# space-separated list of source files
SRCS = server.c staff_func.c perso_func.c
 
# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o

