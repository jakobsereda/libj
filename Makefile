CC        := gcc
CFLAGS    := -Wall -Werror -Wextra -g -fPIC

SRCDIR    := src
SRCS      := $(shell find $(SRCDIR) -name '*.c')
OBJS      := $(SRCS:.c=.o)
TARGET    := libj.so

TESTDIR   := tests
TESTSRCS  := $(shell find $(TESTDIR) -name 'test_*.c')
TESTOBJS  := $(TESTSRCS:.c=.o)
BIN       := tests/bin

INCFILE   := tests/test_include.h
TESTINCS  := $(shell find $(TESTDIR) -name 'test_*.h')
TESTINCS  := $(filter-out $(INCFILE), $(TESTINCS))
TESTINCS  := $(patsubst $(TESTDIR)/%, %, $(TESTINCS))

.PHONY: all clean test inc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(OBJS)
	$(RM) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(TESTOBJS) $(TARGET)
	$(CC) $(CFLAGS) -o $(BIN) $(TESTOBJS) -L. -lj
	$(RM) $(TESTOBJS)

inc:
	@echo "#ifndef TEST_INCLUDE_H" > $(INCFILE)
	@echo -e "#define TEST_INCLUDE_H\n" >> $(INCFILE)
	@for header in $(TESTINCS); do \
		echo "#include \"$$header\"" >> $(INCFILE); \
	done
	@echo -e "\n#endif" >> $(INCFILE)

test: inc $(BIN)
	LD_LIBRARY_PATH=. ./$(BIN)

clean:
	$(RM) $(TARGET) $(BIN)
