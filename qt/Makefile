include ../Makefile.include

CXXFLAGS += $(QT_CXXFLAGS)
LDFLAGS += $(QT_LDFLAGS)

TARGETS = libqt.a test
OBJS = obj_widget.o obj_style_widget.o widget_stack.o \
       main_window.o

all: $(TARGETS)

libqt.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

test: test.o test_win.o $(OBJS) libqt.a
	$(CXX) $(CXXFLAGS) -o test test.o test_win.o $(LDFLAGS) -L./ -lqt

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj_widget.cpp: obj_widget.moc
obj_style_widget.cpp: obj_style_widget.moc
test_win.cpp: test_win.moc
main_window.cpp: main_window.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc
	rm -f *.a

.PHONY: all clean
