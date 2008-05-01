CXXFLAGS += $(COIN_CXXFLAGS) $(QT_CXXFLAGS) $(SOQT_CXXFLAGS)

TARGETS = libcommon.a
OBJS = viewer.o toggle_push_button.o objdata.o \
       style_dialog.o config_dialog.o default_style_dialog.o \
	   coin3dtools.o

all: $(TARGETS)

libcommon.a: $(OBJS)
	ar cr $@ $^
	ranlib $@
	touch ../apps/*.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

toggle_push_button.cpp: toggle_push_button.moc
style_dialog.cpp: style_dialog.moc
default_style_dialog.cpp: default_style_dialog.moc
viewer.cpp: viewer.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc

.PHONY: all clean
