CC=gcc
CFLAGS=-Wall -g
OBJS = main.o myutils.o wav_tools.o crop.o convert.o reverse.o

all: project3



project3: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o project3

main.o: main.c myutils.h wav_tools.h convert.h reverse.h
	$(CC) $(CFLAGS) main.c -c

myutils.o: myutils.c myutils.h
	$(CC) $(CFLAGS) myutils.c -c	

wav_tools.o: wav_tools.c wav_tools.h
	$(CC) $(CFLAGS) wav_tools.c -c

crop.o: crop.c wav_tools.h
	$(CC) $(CFLAGS) crop.c -c

convert.o: convert.c wav_tools.h
	$(CC) $(CFLAGS) convert.c -c

reverse.o: reverse.c wav_tools.h
	$(CC) $(CFLAGS) reverse.c -c


.PHONY: clean all

clean: 
	rm -f $(OBJS) 