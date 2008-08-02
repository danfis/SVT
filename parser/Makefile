CC = gcc
FLEX = flex

CFLAGS = -g -Wall -pedantic -std=gnu99

TARGETS = libsvtparser.a
OBJS = lexer.o parse_func.o parser.o obj.o

all: $(TARGETS)

libsvtparser.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

lexer.c: lexer.l
	$(FLEX) -o $@ $<
lexer.o: lexer.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f lexer.c
	$(MAKE) -C testsuites clean

check:
	$(MAKE) -C testsuites check

check-valgrind:
	$(MAKE) -C testuitest check-valgrind

.PHONY: all clean check check-valgrind
