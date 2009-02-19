include ../Makefile.include

CXXFLAGS += $(QT_CXXFLAGS)

TEST_LDFLAGS = -L./ -L../qt -lsvtqt -lsvtqt2d \
			   -L../parser -lsvtparser \
               $(QT_LDFLAGS)


TARGETS = libsvtqt2d.a test
OBJS = painter.o elements.o points.o edges.o faces.o obj.o main_window.o

all: $(TARGETS)

libsvtqt2d.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

viewer.cpp: viewer.moc
viewer_live.cpp: viewer_live.moc
painter.cpp: painter.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

test: test.o libsvtqt2d.a
	$(CC) $(CXXFLAGS) -o $@ $< $(TEST_LDFLAGS)

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc

.PHONY: all clean
