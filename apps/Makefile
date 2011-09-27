include ../Makefile.include

CXXFLAGS += $(QT_CXXFLAGS) $(COIN_CXXFLAGS) $(QUARTER_CXXFLAGS)
CXXFLAGS += $(CAIRO_CXXFLAGS)
LDFLAGS = -L../parser -lsvtparser \
          -L../coin3d -lsvtcoin3d \
          -L../qt -lsvtqt \
          -L../common -lsvtcommon \
          -lfl \
          $(QT_LDFLAGS) $(COIN_LDFLAGS) $(QUARTER_LDFLAGS) \
		  $(CAIRO_LDFLAGS)

SVT_DEPS = ../parser/libsvtparser.a \
           ../coin3d/libsvtcoin3d.a \
           ../qt/libsvtqt.a \
           ../common/libsvtcommon.a

TARGETS = svt svt-viewer-3d svt-viewer-2d svt-to-svg svt-viewer-3d-live \
          svt-viewer-2d-live svt-to-png svt-to-pov
OBJS = main.o to-svg.o to-png.o to-pov.o viewer-2d3d-live.o viewer-2d3d.o

all: $(TARGETS)

svt: $(OBJS) $(SVT_DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)
svt-viewer-3d: svt
	rm -f $@; ln $< $@
svt-viewer-3d-live: svt
	rm -f $@; ln $< $@
svt-viewer-2d-live: svt
	rm -f $@; ln $< $@
svt-to-svg: svt
	rm -f $@; ln $< $@
svt-to-png: svt
	rm -f $@; ln $< $@
svt-to-pov: svt
	rm -f $@; ln $< $@
svt-viewer-2d: svt
	rm -f $@; ln $< $@


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
