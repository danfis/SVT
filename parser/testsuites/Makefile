CC = gcc

CUDIR ?= ../../cu/
CHECK_REG=$(CUDIR)/check-regressions

CFLAGS = -g -Wall -pedantic -std=gnu99 \
		 -I./ -I../ -I$(CUDIR)
LDFLAGS = -L./ -L../ -L$(CUDIR) -lcu -lsvtparser -lm

OBJS = obj.o parser.o

all: test

test: ../libsvtparser.a $(OBJS)
	$(CC) $(CFLAGS) -o $@ main.c $(OBJS) $(LDFLAGS)

../libsvtparser.a:
	$(MAKE) -C ../ libsvtparser.a

%.o: %.c %.h ../%.c ../%.h
	$(CC) $(CFLAGS) -c -o $@ $<
objs/%.o: ../%.c ../%.h
	$(CC) $(CFLAGS) -c -o $@ $<
objs/%.o: ../%.c
	$(CC) $(CFLAGS) -c -o $@ $<

check: all
	@echo ""
	@echo "----------------------------------------";
	./test
	@echo "----------------------------------------";
	@echo "Checking regressions:";
	cd regressions && ../$(CHECK_REG)
	@echo ""
check-valgrind: all
	valgrind -q --leak-check=full --show-reachable=yes --trace-children=yes ./test

clean:
	rm -f *.o
	rm -f objs/*.o
	rm -f test
	rm -f tmp.*
	rm -f regressions/tmp.*

.PHONY: all clean check
	
