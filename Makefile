# TODO: support out-of-source build either via cmake or vpath stuff

CC := gcc
CFLAGS := -Wall -W -g -O -std=c99
DEFINES := -D_GNU_SOURCE
INCLUDES := -Iinclude
CPPFLAGS := $(DEFINES) $(INCLUDES)

AR := ar

BINARIES :=

.PHONY: all
all: lib tests

.PHONY: lib
lib: lib/libfailpoint.a
lib/libfailpoint.a: src/failpoint.o
	mkdir -p lib
	$(AR) crv $@ $^

.PHONY: tests
tests: test/failpoint_test
test/failpoint_test: test/failpoint_test.o test/run.o test/foo.o test/bar.o 
	$(CC) -o $@ $^ lib/libfailpoint.a
BINARIES += test/failpoint_test

clean:
	rm -rf lib
	rm -f src/*.o
	rm -f test/*.o
	rm -f $(BINARIES)
