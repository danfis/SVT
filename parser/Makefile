include ../Makefile.include
LDFLAGS += -lm

CFLAGS += -Wall -pedantic -std=gnu99

TARGETS = libsvtparser.a test-parse
#OBJS = lexer.o parse_func.o parser.o obj.o
OBJS = svt.parser.o svt.lex.o parse_func.o obj.o

all: $(TARGETS)

libsvtparser.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

test-parse: test-parse-main.o libsvtparser.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -L. -lsvtparser

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

svt.lex.c: svt.l
	$(FLEX) --noline --header-file=svt.lex.h -o $@ $<
svt.parser.c: svt.y
	$(BISON) -v --defines=svt.parser.h -o $@ $<
test-parse-main.o: test-parse-main.c svt.parser.c
	$(CC) $(CFLAGS) -c -o $@ $<
svt.parser.o: svt.parser.c svt.lex.c
	$(CC) $(CFLAGS) -c -o $@ $<
svt.lex.o: svt.lex.c svt.parser.c
	$(CC) $(CFLAGS) -c -o $@ $<

lexer.c: lexer.l
	$(FLEX) --nounput --header-file=lexer_gen.h -o $@ $<
lexer.o: lexer.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f lexer.c lexer_gen.h
	rm -f svt.lex.* svt.parser.*
	$(MAKE) -C testsuites clean

check:
	$(MAKE) -C testsuites check

check-valgrind:
	$(MAKE) -C testuitest check-valgrind

.PHONY: all clean check check-valgrind
