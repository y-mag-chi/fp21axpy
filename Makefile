# pgi compiler
CC = pgcc
CXX = pgc++

OBJS = main.o saxpy.o

PROGRAM = saxpy.exe

CFLAGS = -O3
CFLAGS += -acc -Minfo=accel
CFLAGS += -ta=tesla:ccall,loadcache:L1,fastmath

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) *.o -o $(PROGRAM)

.c.o:
	$(CC) $(CFLAGS) -c $<
.cpp.o:
	$(CXX) $(CFLAGS) -c $<

clean: FORCE
	rm -f *.o *.exe *~
run:
	sh run.sh
FORCE:
