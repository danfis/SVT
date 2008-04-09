CXXFLAGS += -I../common

TARGETS = libparser.a
OBJS = parser.o lexer.o

all: $(TARGETS)

libparser.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lexer.c: lexer.l
	$(FLEX) -o $@ $<
lexer.o: lexer.c
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc
	rm -f lexer.c

.PHONY: all clean
