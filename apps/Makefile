include ../Makefile.include

CXXFLAGS += -I../common -I../parser $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS_COIN = -L../common -L../parser -lsvtparser -lcommon -lfl $(COIN_LDFLAGS) $(SOQT_LDFLAGS) $(QT_LDFLAGS)
LDFLAGS_TO_SVG = -L../parser -lsvtparser -lfl

TARGETS = coin-viewer coin-iv-viewer coin-viewer-live svt-to-svg
VIEWER_OBJS = viewer.o viewer-common.o common_coin.o settings.o
IV_VIEWER_OBJS = iv-viewer.o
VIEWER_LIVE_OBJS = viewer-live.o viewer-live-common.o common_coin.o settings.o
TO_SVG_OBJS = to-svg.o to-svg-common.o to-svg-settings.o

all: $(TARGETS)

coin-viewer: $(VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_COIN)
coin-iv-viewer: $(IV_VIEWER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_COIN)
coin-viewer-live: $(VIEWER_LIVE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_COIN) -lpthread
svt-to-svg: $(TO_SVG_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_TO_SVG)

viewer.o: viewer.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
viewer-live.o: viewer-live.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

viewer-common.o: common.cpp common.hpp
	$(CXX) $(CXXFLAGS) -DVIEWER -c -o $@ $<
viewer-live-common.o: common.cpp common.hpp
	$(CXX) $(CXXFLAGS) -DVIEWER_LIVE -c -o $@ $<

to-svg-common.o: common.cpp common.hpp
	$(CXX) $(CXXFLAGS) -DTO_SVG -c -o $@ $<
to-svg-settings.o: settings.cpp settings.hpp
	$(CXX) $(CXXFLAGS) -DTO_SVG -c -o $@ $<

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~

.PHONY: all clean
