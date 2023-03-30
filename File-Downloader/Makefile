CC = gcc
CFLAGS = -Wall -pedantic -std=c99
MAIN = downloader
OBJS = downloader.o

all: $(MAIN)

$(MAIN) : $(OBJS) downloader.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

downloader.o: downloader.c downloader.h
	$(CC) $(CFLAGS) -c downloader.c -g -lcurl
