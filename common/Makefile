include ../Makefile.include

CXXFLAGS += $(COIN_CXXFLAGS) $(QT_CXXFLAGS) $(SOQT_CXXFLAGS)

TARGETS = libsvtcommon.a
OBJS = settings.o functions.o obj.o

all: $(TARGETS)

libsvtcommon.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc

.PHONY: all clean
