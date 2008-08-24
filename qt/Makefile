include ../Makefile.include

CXXFLAGS += $(QT_CXXFLAGS)

TARGETS = obj_widget.o
OBJS =

all: $(TARGETS)

libcommon.a: $(OBJS)
	ar cr $@ $^
	ranlib $@
	touch ../apps/*.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj_widget.cpp: obj_widget.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc

.PHONY: all clean
