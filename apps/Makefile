CXXFLAGS += -I../common -I../parser $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS += -L../common -L../parser -lparser -lcommon -lfl $(COIN_LDFLAGS) $(SOQT_LDFLAGS) $(QT_LDFLAGS)

TARGETS = viewer iv-viewer viewer-live
VIEWER_OBJS = viewer.o
IV_VIEWER_OBJS = iv-viewer.o
VIEWER_LIVE_OBJS = viewer-live.o

all: $(TARGETS)

viewer: $(VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
iv-viewer: $(IV_VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
viewer-live: $(VIEWER_LIVE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lpthread

%.o: %.cpp %.hpp
	$(CXX) $(VIEWER_CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~

.PHONY: all clean
