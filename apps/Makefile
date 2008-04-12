CXXFLAGS += -I../common -I../parser $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS += -L../common -L../parser -lparser -lcommon -lfl $(COIN_LDFLAGS) $(SOQT_LDFLAGS) $(QT_LDFLAGS)

TARGETS = viewer iv-viewer
VIEWER_OBJS = viewer.o
IV_VIEWER_OBJS = iv-viewer.o

all: $(TARGETS)

viewer: $(VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
iv-viewer: $(IV_VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(VIEWER_CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~

.PHONY: all clean
