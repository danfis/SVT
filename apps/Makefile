CXXFLAGS += -I../common -I../parser $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS += -L../common -L../parser -lparser -lcommon -lfl $(COIN_LDFLAGS) $(SOQT_LDFLAGS) $(QT_LDFLAGS)

TARGETS = coin-viewer coin-iv-viewer coin-viewer-live
VIEWER_OBJS = viewer.o
IV_VIEWER_OBJS = iv-viewer.o
VIEWER_LIVE_OBJS = viewer-live.o

all: $(TARGETS)

coin-viewer: $(VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
coin-iv-viewer: $(IV_VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
coin-viewer-live: $(VIEWER_LIVE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lpthread

viewer.o: viewer.cpp viewer_common.cpp viewer_common_main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
viewer-live.o: viewer-live.cpp viewer_common.cpp viewer_common_main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~

.PHONY: all clean
