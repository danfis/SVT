include ../Makefile.include

CXXFLAGS += $(QT_CXXFLAGS)
LDFLAGS += $(QT_LDFLAGS)

TARGETS = libsvtqt.a test
OBJS = obj_widget.o obj_style_widget.o widget_stack.o \
       main_window.o config.o

all: $(TARGETS)

libsvtqt.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

test: test.o libsvtqt.a
	$(CXX) $(CXXFLAGS) -o test test.o $(LDFLAGS) -L./ -lsvtqt

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj_widget.cpp: obj_widget.moc
obj_style_widget.cpp: obj_style_widget.moc
main_window.cpp: main_window.moc
config.cpp: config.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc
	rm -f *.a

.PHONY: all clean
