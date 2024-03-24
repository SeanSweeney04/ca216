CC = gcc
CFLAGS = -Wall

SRCS = myshell.c utility.c

HDRS = myshell.h

TARGET = myshell

$(TARGET) : $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
