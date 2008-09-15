include ../Makefile.include

CXXFLAGS += $(COIN_CXXFLAGS) $(QT_CXXFLAGS) $(SOQT_CXXFLAGS)

TARGETS =
OBJS =

all: $(TARGETS)

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
