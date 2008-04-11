CXXFLAGS += $(COIN_CXXFLAGS) $(QT_CXXFLAGS) $(SOQT_CXXFLAGS)

TARGETS = libcommon.a
OBJS = viewer.o viewer_push_button.o objdata.o \
       style_window.o

all: $(TARGETS)

libcommon.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

viewer_push_button.cpp: viewer_push_button.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc
	rm -f lexer.c

.PHONY: all clean
