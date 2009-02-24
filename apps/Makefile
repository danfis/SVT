include ../Makefile.include

LDFLAGS_ALL = -lfl \
              -L../parser -lsvtparser \
              -L../common -lsvtcommon

CXXFLAGS_2D = $(CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS_2D = $(LDFLAGS_ALL) \
             -L../qt -lsvtqt \
             -L../qt2d -lsvtqt2d \
             $(QT_LDFLAGS)

CXXFLAGS_3D = $(CXXFLAGS) $(QT_CXXFLAGS) $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS)
LDFLAGS_3D = $(LDFLAGS_ALL) \
             -L../coin3d -lsvtcoin3d \
             -L../qt -lsvtqt \
             $(QT_LDFLAGS) $(COIN_LDFLAGS) $(SOQT_LDFLAGS)

CXXFLAGS_SVG = $(CXXFLAGS) $(QT_CXXFLAGS)
LDFLAGS_SVG = $(LDFLAGS_ALL)

TARGETS = svt-viewer svt-to-svg svt-viewer-2d
#IV_VIEWER_OBJS = iv-viewer.o
#VIEWER_LIVE_OBJS = viewer-live.o viewer-live-common.o common_coin.o settings.o

all: $(TARGETS)

svt-viewer: viewer-3d.cpp
	$(CXX) $(CXXFLAGS_3D) -o $@ $^ $(LDFLAGS_3D)
svt-to-svg: to-svg.cpp
	$(CXX) $(CXXFLAGS_SVG) -o $@ $^ $(LDFLAGS_SVG)
svt-viewer-2d: viewer-2d.cpp
	$(CXX) $(CXXFLAGS_2D) -o $@ $^ $(LDFLAGS_2D)


#svt-iv-viewer: $(IV_VIEWER_OBJS)
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_COIN)
#svt-viewer-live: $(VIEWER_LIVE_OBJS)
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_COIN) -lpthread
#viewer-live.o: viewer-live.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<
#viewer-live-common.o: common.cpp common.hpp
#	$(CXX) $(CXXFLAGS) -DVIEWER_LIVE -c -o $@ $<
#to-svg-common.o: common.cpp common.hpp
#	$(CXX) $(CXXFLAGS) -DTO_SVG -c -o $@ $<
#to-svg-settings.o: settings.cpp settings.hpp
#	$(CXX) $(CXXFLAGS) -DTO_SVG -c -o $@ $<

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~

.PHONY: all clean
