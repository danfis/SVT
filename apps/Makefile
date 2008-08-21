CXXFLAGS += -I../common -I../parser $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS += -L../common -L../parser -lsvtparser -lcommon -lfl $(COIN_LDFLAGS) $(SOQT_LDFLAGS) $(QT_LDFLAGS)

TARGETS = coin-viewer coin-iv-viewer coin-viewer-live
VIEWER_OBJS = common-viewer.o viewer.o
IV_VIEWER_OBJS = iv-viewer.o
VIEWER_LIVE_OBJS = common-viewer-live.o viewer-live.o

all: $(TARGETS)

coin-viewer: $(VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
coin-iv-viewer: $(IV_VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
coin-viewer-live: $(VIEWER_LIVE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lpthread

viewer.o: viewer.cpp viewer_common_main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
viewer-live.o: viewer-live.cpp viewer_common_main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

common-viewer.o: common.cpp common.hpp
	$(CXX) $(CXXFLAGS) -DVIEWER -c -o $@ $<
common-viewer-live.o: common.cpp common.hpp
	$(CXX) $(CXXFLAGS) -DVIEWER_LIVE -c -o $@ $<

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~

.PHONY: all clean
