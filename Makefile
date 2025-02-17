CC     := gcc
CFLAGS := -Wall -Werror -Wextra -g -fPIC
SRCDIR := src/
SRCS   := $(shell find $(SRCDIR) -name '*.c')
OBJS   := $(SRCS:.c=.o)
TARGET := libj.so

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(OBJS)
	$(RM) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET)
