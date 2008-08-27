include ../Makefile.include

CXXFLAGS += $(QT_CXXFLAGS)
LDFLAGS += $(QT_LDFLAGS)

TARGETS = test obj_widget.o obj_style_widget.o
OBJS =

all: $(TARGETS)

libcommon.a: $(OBJS)
	ar cr $@ $^
	ranlib $@
	touch ../apps/*.cpp

test: test.o test_win.o obj_widget.o obj_style_widget.o
	$(CXX) $(CXXFLAGS) -o test $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj_widget.cpp: obj_widget.moc
obj_style_widget.cpp: obj_style_widget.moc
test_win.cpp: test_win.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc

.PHONY: all clean
