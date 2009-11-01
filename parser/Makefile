include ../Makefile.include

CFLAGS += -Wall -pedantic -std=gnu99

TARGETS = libsvtparser.a
OBJS = lexer.o parse_func.o parser.o obj.o

all: $(TARGETS)

libsvtparser.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

parser.h: lexer_gen.h
lexer_gen.h: lexer.c
lexer.c: lexer.l
	$(FLEX) --header-file=lexer_gen.h -o lexer.c $<
lexer.o: lexer.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f lexer.c lexer_gen.h
	$(MAKE) -C testsuites clean

check:
	$(MAKE) -C testsuites check

check-valgrind:
	$(MAKE) -C testuitest check-valgrind

.PHONY: all clean check check-valgrind
