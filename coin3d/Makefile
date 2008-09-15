include ../Makefile.include

CXXFLAGS += $(COIN_CXXFLAGS) $(QT_CXXFLAGS) $(SOQT_CXXFLAGS)

TEST_LDFLAGS = -L./ -lsvtcoin3d -L../qt -lsvtqt \
               $(QT_LDFLAGS) $(COIN_LDFLAGS) $(SOQT_LDFLAGS)


TARGETS = libsvtcoin3d.a test
OBJS = obj.o obj_manager.o coin3d.o

all: $(TARGETS)

libsvtcoin3d.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

test: libsvtcoin3d.a
	$(CXX) $(CXXFLAGS) -o $@ test.cpp $(TEST_LDFLAGS)
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc

.PHONY: all clean
