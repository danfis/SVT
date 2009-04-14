include ../Makefile.include

CXXFLAGS += $(COIN_CXXFLAGS) $(QT_CXXFLAGS) $(QUARTER_CXXFLAGS)

TEST_LDFLAGS = -L./ -lsvtcoin3d -L../qt -lsvtqt \
               $(QT_LDFLAGS) $(COIN_LDFLAGS) $(SOQT_LDFLAGS)


TARGETS = libsvtcoin3d.a
OBJS = obj.o obj_manager.o main_window.o viewer.o
#coin3d.o viewer.o viewer_live.o

all: $(TARGETS)

libsvtcoin3d.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

config.cpp: config.moc
main_window.cpp: main_window.moc
viewer.cpp: viewer.moc
viewer_live.cpp: viewer_live.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc

.PHONY: all clean
