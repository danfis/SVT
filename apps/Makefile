CXXFLAGS += -I../common -I../parser $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS += -L../common -L../parser -lparser -lcommon -lfl $(COIN_LDFLAGS) $(SOQT_LDFLAGS) $(QT_LDFLAGS)

TARGETS = viewer
OBJS = viewer.o

all: $(TARGETS)

viewer: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(VIEWER_CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc
	rm -f lexer.c

.PHONY: all clean
